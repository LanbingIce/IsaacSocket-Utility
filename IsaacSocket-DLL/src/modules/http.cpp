#include "module.hpp"
#include "handle.hpp"
#include "function.hpp"
#include "async.hpp"

namespace http {

struct TempFiles {
    std::vector<std::wstring> files;

    TempFiles() = default;
    TempFiles(TempFiles const &) = delete;
    TempFiles &operator=(TempFiles const &) = delete;
    TempFiles(TempFiles &&) = default;
    TempFiles &operator=(TempFiles &&) = default;

    ~TempFiles() {
        for (auto&& f : files) {
            DeleteFileW(f.c_str());
        }
    }

    std::string createTempFile(std::string const &content = {}, std::string const &suffix = {}) {
        wchar_t tmppath[MAX_PATH - 14]{};
        GetTempPathW(MAX_PATH - 13, tmppath);
        wchar_t filename[MAX_PATH + 5]{};
        GetTempFileNameW(tmppath, L"tmp", 0, filename);
        std::wstring wres = filename;
        if (wres.empty()) [[unlikely]] {
            throw std::runtime_error("could not allocate a temp file: " + std::to_string(GetLastError()));
        }
        if (!suffix.empty()) {
            wres += utils::U8ToU16(suffix);
        }
        auto res = utils::U16ToU8(wres);
        HANDLE h = CreateFileW(wres.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
        if (h == INVALID_HANDLE_VALUE) [[unlikely]] {
            throw std::runtime_error("could not create a temp file: " + std::to_string(GetLastError()));
        }
        files.emplace_back(std::move(wres));
        if (!content.empty()) {
            if (!WriteFile(h, content.data(), content.size(), NULL, NULL)) [[unlikely]] {
                CloseHandle(h);
                throw std::runtime_error("could not write to the temp file: " + std::to_string(GetLastError()));
            }
        }
        CloseHandle(h);
        return res;
    }

};

static HANDLE executeCommand(std::vector<std::string> const &args) {
    BOOL bSuccess = FALSE;

    PROCESS_INFORMATION piProcInfo; 
    STARTUPINFOW siStartInfo;
    ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
    ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
    siStartInfo.cb = sizeof(STARTUPINFO); 
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    std::ostringstream ss;
    for (auto const &arg : args) {
        ss << std::quoted(arg, '"', '"') << ' ';
        /* ss << arg << ' '; */
        /* _cprintf("%s\n", arg.c_str()); */
        /* if (ss.str().size() < 10) continue; */
        /* _cprintf("%s\n", ss.str().substr(ss.str().size() - 8).c_str()); */
    }
    cw("command >>>", ss.str());
    /* _cprintf("%s\n", ss.str().c_str()); */
    std::wstring cmdLine = utils::U8ToU16(ss.str());
    bSuccess = CreateProcessW( utils::U8ToU16(args[0]).c_str(),
    /* std::string cmdLine = utils::U16ToAnsi(utils::U8ToU16(ss.str())); */
    /* bSuccess = CreateProcessA( utils::U16ToU8(utils::U8ToU16(args[0])).c_str(), */
      cmdLine.data(),       // command line
      NULL,                 // process security attributes
      NULL,                 // primary thread security attributes
      TRUE,                 // handles are inherited
      0,                    // creation flags
      NULL,                 // use parent's environment
      NULL,                 // use parent's current directory
      &siStartInfo,         // STARTUPINFO pointer
      &piProcInfo );        // receives PROCESS_INFORMATION
    if( !bSuccess ) return NULL;
    CloseHandle(piProcInfo.hThread);
    return piProcInfo.hProcess;
}

static int Request(lua_State* L) {
    auto temps = std::make_shared<TempFiles>();

    ARG(1, stdstring, std::string, method);
    ARG(2, stdstring, std::string, url);
    ARG_DEF(3, stdstring, std::string, content, {});
    ARG_DEF(4, stdstring, std::string, contentType, {});
    ARG_DEF(5, mapstringstring, decltype(std::map<std::string, std::string>()), headers, {});
    ARG_DEF(6, mapstringstring, decltype(std::map<std::string, std::string>()), cookies, {});
    ARG_DEF(7, integer, int, timeout, 0);
    ARG_DEF(8, stdstring, std::string, bodyFilePath, {});

    std::vector<std::string> args;
    args.reserve(8);
    const char *curlPath = "curl";
#ifdef __MINGW32__ // 小彭老师专有路径
    curlPath = "Z:\\home\\bate\\Codes\\IsaacSocket-Utility\\IsaacSocket-DLL\\bin\\curl.exe";
#endif
    args.push_back(curlPath);
    args.push_back(url);
    if (!method.empty()) {
        /* if (method == "GET") { */
        /*     args.push_back("--get"); */
        /* } else { */
            args.push_back("-X");
            args.push_back(method);
        /* } */
    }
    auto outFile = bodyFilePath.empty() ? temps->createTempFile() : bodyFilePath;
    auto hdrFile = temps->createTempFile();
    args.push_back("--output");
    args.push_back(outFile);
    args.push_back("--dump-header");
    args.push_back(hdrFile);
    if (!content.empty()) {
        auto tmpFile = temps->createTempFile(content);
        args.push_back("--data-binary");
        args.push_back("@" + tmpFile);
    }
    if (!cookies.empty()) {
        for (auto const &[k, v] : cookies) {
            args.push_back("--cookie");
            args.push_back(k + "=" + v);
        }
    }
    if (!contentType.empty()) {
        args.push_back("-H");
        args.push_back("Content-Type: " + contentType);
    }
    if (!headers.empty()) {
        for (auto const &[k, v] : headers) {
            args.push_back("-H");
            args.push_back(k + ": " + v);
        }
    }
    if (timeout > 0) {
        args.push_back("--max-time");
        args.push_back(std::to_string(timeout));
    }
    args.push_back("--silent");
    args.push_back("--location");

    HANDLE hProc = executeCommand(args);
    if (!hProc) [[unlikely]] {
        throw std::runtime_error("could not spawn the child process: " + std::to_string(GetLastError()));
    }

    ASYNC_BEGIN(hProc, temps, outFile, hdrFile);
    DWORD ret = STATUS_PENDING;
    GetExitCodeProcess(hProc, &ret);
    if (ret == STATUS_PENDING) {
        ASYNC_YIELD();
    }
    cw("exit", ret);
    CloseHandle(hProc);

    struct Result {
        std::string body;
        std::string headers;
    };

    /* read the response from the temp file */
    std::ifstream is(std::filesystem::path((const char8_t *)outFile.c_str()), std::ios::binary);
    std::string body(std::istreambuf_iterator<char>(is), {});
    is.close();
    /* read the headers from the temp file */
    std::ifstream isf(std::filesystem::path((const char8_t *)hdrFile.c_str()), std::ios::binary);
    std::string headers(std::istreambuf_iterator<char>(isf), {});
    isf.close();

    auto res = std::make_shared<Result>();
    res->body = std::move(body);
    res->headers = std::move(headers);

    ASYNC_RET(ret, res);
    if (ret != 0) [[unlikely]] {
        RET_TABLE();
        RET_TABLE_KEY(string, "error", integer, (int)ret);
        RET_TABLE_KEY(string, "status", integer, 0);
        RET_TABLE_END();
    } else {
        auto headers = std::move(res->headers);
        auto body = std::move(res->body);
        cw(headers);
        cw(body.size());
        if (headers.empty()) [[unlikely]] {
            RET_TABLE();
            RET_TABLE_KEY(string, "error", integer, -99);
            RET_TABLE_KEY(string, "status", integer, 0);
            RET_TABLE_KEY(string, "body", stdstringview, body);
            RET_TABLE_END();
        }
        /* remove the first line */
        std::istringstream iss(headers);
        std::string line;
        std::map<std::string, std::string> h;
        std::string reason;
        int status = 0;
        while (std::getline(iss, line, '\n')) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue;
            if (line.starts_with("HTTP/")) {
                auto pos = line.find(' ', 4);
                if (pos != std::string_view::npos) {
                    status = std::atoi(line.c_str() + pos);
                    pos = line.find(' ', pos + 1);
                }
                if (pos != std::string_view::npos) {
                    reason = line.substr(pos + 1);
                }
            } else {
                auto pos = line.find(':');
                if (pos != std::string_view::npos) {
                    auto key = line.substr(0, pos);
                    auto an = line.find_first_not_of(' ', pos + 1);
                    auto value = an == std::string_view::npos ? std::string() : line.substr(an);
                    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
                    std::replace(key.begin(), key.end(), '-', '_');
                    h.try_emplace(key, std::move(value));
                }
            }
        }
        RET_TABLE();
        RET_TABLE_KEY(string, "error", integer, 0);
        RET_TABLE_KEY(string, "status", integer, status);
        RET_TABLE_KEY(string, "reason", stdstring, reason);
        RET_TABLE_KEY(string, "headers", mapstringstring, h);
        RET_TABLE_KEY(string, "body", stdstringview, body);
        RET_TABLE_END();
    }
    ASYNC_END();

    /* ASYNC_BEGIN(=); */
    /* auto resp = std::make_shared<httplib::Result>(cli.PostEx(method, uri, headers, content.data(), content.size(), contentType)); */
    /* ASYNC_RET(=); */
    /* auto &res = *resp; */
    /* if (!res) [[unlikely]] { */
    /*     RET_TABLE(); */
    /*     RET_TABLE_KEY(string, "error", integer, (int)res.error()); */
    /*     RET_TABLE_KEY(string, "status", integer, 0); */
    /*     RET_TABLE_KEY(string, "reason", string, httpErrorString(res.error())); */
    /*     RET_TABLE_END(); */
    /* } */
    /* RET_TABLE(); */
    /* RET_TABLE_KEY(string, "error", integer, 0); */
    /* RET_TABLE_KEY(string, "status", integer, res->status); */
    /* RET_TABLE_KEY(string, "body", stdstringview, res->body); */
    /* RET_TABLE_KEY(string, "reason", stdstringview, res->reason); */
    /* RET_TABLE_KEY(string, "location", stdstringview, res->location); */
    /* RET_TABLE_KEY(string, "headers", mapstringstring<httplib::Headers>, res->headers); */
    /* RET_TABLE_END(); */
    /* ASYNC_END(); */
}

/* example:
if IsaacSocket and Input.IsButtonTriggered(Keyboard.KEY_A, 0) then
    local job = IsaacSocket.Http.Request("https://www.lua.org/manual/5.2/manual.html", "GET", {key = "val"}):Then(function (res)
        if res.status == 200 then
            print(res.body)
        end
    end)
    -- you may optionally call job:Cancel() to try cancel the job
end
*/

static RegisterModule Init = [] {
    MODULE_BEGIN(Http);
    MODULE_FUNC(Request);
    MODULE_END();
};

}

#pragma once

#include "pch.h"

enum Handle : uintptr_t { NULL_HANDLE = 0 };

template <typename T>
struct HandleTable {
private:
    struct Hash : std::hash<T *> {
        size_t operator()(std::unique_ptr<T> const &handle) const {
            return std::hash<T *>::operator()(handle.get());
        }
        using std::hash<T *>::operator();
        using is_transparent = std::true_type;
    };

    struct Eq : std::equal_to<T *> {
        bool operator()(std::unique_ptr<T> const &lhs, std::unique_ptr<T> const &rhs) const {
            return lhs.get() == rhs.get();
        }
        bool operator()(std::unique_ptr<T> const &lhs, T *const &rhs) const {
            return lhs.get() == rhs;
        }
        bool operator()(T *const &lhs, std::unique_ptr<T> const &rhs) const {
            return lhs == rhs.get();
        }
        using std::equal_to<T *>::operator();
        using is_transparent = std::true_type;
    };

    std::unordered_set<std::unique_ptr<T>, Hash, Eq> handles;

public:
    HandleTable() = default;
    HandleTable(HandleTable &&) = delete;

    Handle create(std::unique_ptr<T> &&handle) {
        auto ptr = handle.get();
        if (ptr) [[likely]] {
            handles.insert(std::move(handle));
        }
        return Handle(reinterpret_cast<uintptr_t>(ptr));
    }

    T *find(Handle handle) {
        auto ptr = reinterpret_cast<T *>(handle);
        auto it = handles.find(ptr);
        if (it == handles.end()) [[unlikely]] {
            return nullptr;
        }
        return it->get();
    }

    void destroy(Handle handle) {
        auto ptr = reinterpret_cast<T *>(handle);
        auto it = handles.find(ptr);
        if (it == handles.end()) [[unlikely]] {
            return;
        }
        handles.erase(it);
    }
};

template <typename K, typename V>
struct KVCache {
private:
    std::unordered_map<K, V> entries;

public:
    KVCache() = default;
    KVCache(KVCache &&) = delete;

    V *create(K key, V &&value) {
        auto it = entries.find(key);
        if (it != entries.end()) [[unlikely]] {
            return nullptr;
        }
        return &entries.emplace(std::move(key), std::move(value)).first->second;
    }

    template <typename VGen> requires std::is_invocable_r_v<V, VGen>
    V &find(K key, VGen &&valueGenerator) {
        auto it = entries.find(key);
        if (it != entries.end()) [[unlikely]] {
            return it->second;
        }
        return entries.emplace(std::move(key), valueGenerator()).first->second;
    }

    template <typename VGen> requires std::is_invocable_r_v<V, VGen, K const &>
    V &find(K key, VGen &&valueGenerator) {
        auto it = entries.find(key);
        if (it != entries.end()) [[unlikely]] {
            return it->second;
        }
        return entries.emplace(std::move(key), valueGenerator(static_cast<K const &>(key))).first->second;
    }

    V &find(K key, V &&defaultValue) {
        auto it = entries.find(key);
        if (it != entries.end()) [[unlikely]] {
            return it->second;
        }
        return entries.emplace(std::move(key), std::move(defaultValue)).first->second;
    }

    V *find(K key) {
        auto it = entries.find(key);
        if (it == entries.end()) [[unlikely]] {
            return nullptr;
        }
        return &it->second;
    }

    void destroy(K key) {
        auto it = entries.find(key);
        if (it == entries.end()) [[unlikely]] {
            return;
        }
        entries.erase(it);
    }
};

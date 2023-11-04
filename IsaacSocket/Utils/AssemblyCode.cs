namespace IsaacSocket.Utils
{
    internal class AssemblyCode
    {
        private class FlagClass
        {
            internal int address;
            internal List<int> sizes = new();
            internal List<int> calcs = new();
            internal List<int> replaces = new();
        }

        private Dictionary<string, FlagClass> flags;
        private int pMem;
        private List<byte> buffer;
        public AssemblyCode(int pMem)
        {
            flags = new();
            this.pMem = pMem;
            buffer = new();
        }
        internal byte[] GetBytes()
        {

            foreach (var kvp in flags)
            {
                for (int i = 0; i < kvp.Value.replaces.Count; i++)
                {
                    int address = kvp.Value.replaces[i];
                    buffer.RemoveRange(address, kvp.Value.sizes[i]);
                    buffer.InsertRange(address, BitConverter.GetBytes(kvp.Value.address - kvp.Value.calcs[i])[0..kvp.Value.sizes[i]]);
                }
            }
            return buffer.ToArray();
        }

        internal void Flag(string flag)
        {
            if (!flags.ContainsKey(flag))
            {
                flags.Add(flag, new());
            }
            flags[flag].address = buffer.Count;
        }
        internal void push_ecx()
        {
            buffer.Add(0x51);
        }
        internal void push_eax()
        {
            buffer.Add(0x50);
        }
        internal void push_esi()
        {
            buffer.Add(0x56);
        }
        internal void push_edi()
        {
            buffer.Add(0x57);
        }


        internal void pop_ecx()
        {
            buffer.Add(0x59);
        }
        internal void pop_esi()
        {
            buffer.Add(0x5E);
        }
        internal void pop_edi()
        {
            buffer.Add(0x5F);
        }

        internal void ret()
        {
            buffer.Add(0xC3);
        }


        internal void push_ptr(int value)
        {
            buffer.Add(0x68);
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void push(int value)
        {
            buffer.Add(0x68);
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void push(byte value)
        {
            buffer.Add(0x6A);
            buffer.Add(value);
        }
        internal void mov_edi_ecx()
        {
            buffer.AddRange(new byte[] { 0x8B, 0xF9 });
        }
        internal void mov_ecx_edi()
        {
            buffer.AddRange(new byte[] { 0x8B, 0xCF });
        }

        internal void cmp_dword_ptr_byte(int value1, byte value2)
        {
            buffer.AddRange(new byte[] { 0x83, 0x3D });
            buffer.AddRange(BitConverter.GetBytes(value1));
            buffer.Add(value2);
        }
        internal void mov_ecx_ptr(int value)
        {
            buffer.AddRange(new byte[] { 0x8B, 0x0D });
            buffer.AddRange(BitConverter.GetBytes(value));

        }
        internal void test_ecx_ecx()
        {
            buffer.AddRange(new byte[] { 0x85, 0xC9 });
        }
        internal void test_eax_eax()
        {
            buffer.AddRange(new byte[] { 0x85, 0xC0 });
        }

        internal void add_ecx(int value)
        {
            buffer.AddRange(new byte[] { 0x81, 0xC1 });
            buffer.AddRange(BitConverter.GetBytes(value));
        }

        internal void xor_edi_edi()
        {
            buffer.AddRange(new byte[] { 0x33, 0xFF });
        }
        internal void xor_esi_esi()
        {
            buffer.AddRange(new byte[] { 0x33, 0xF6 });

        }
        internal void cmp_edi(byte value)
        {
            buffer.AddRange(new byte[] { 0x83, 0xFF });
            buffer.Add(value);

        }


        internal void add_esp(byte value)
        {
            buffer.AddRange(new byte[] { 0x83, 0xC4 });
            buffer.Add(value);
        }
        internal void mov_ecx_esi()
        {
            buffer.AddRange(new byte[] { 0x8B, 0xCE });
        }

        internal void movzx_eax_byte_ptr_esi(byte value)
        {
            buffer.AddRange(new byte[] { 0x0F, 0xB6, 0x46 });
            buffer.Add(value);
        }

        internal void move_esi(int value)
        {
            buffer.AddRange(new byte[] { 0x8B, 0x35 });
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void je(string flag)
        {
            buffer.AddRange(new byte[] { 0x0F, 0x84 });
            if (!flags.ContainsKey(flag))
            {
                flags.Add(flag, new());
            }
            flags[flag].replaces.Add(buffer.Count);
            flags[flag].calcs.Add(buffer.Count + 4);
            flags[flag].sizes.Add(4);
            buffer.AddRange(BitConverter.GetBytes(0));
        }

        internal void je_int32(string flag)
        {
            buffer.Add(0x74);
            if (!flags.ContainsKey(flag))
            {
                flags.Add(flag, new());
            }
            flags[flag].replaces.Add(buffer.Count);
            flags[flag].calcs.Add(buffer.Count + 1);
            flags[flag].sizes.Add(1);
            buffer.Add(0);
        }

        internal void jb(string flag)
        {
            buffer.Add(0x72);
            if (!flags.ContainsKey(flag))
            {
                flags.Add(flag, new());
            }
            flags[flag].replaces.Add(buffer.Count);
            flags[flag].calcs.Add(buffer.Count + 1);
            flags[flag].sizes.Add(1);
            buffer.Add(0);
        }
        internal void ja(string flag)
        {
            buffer.Add(0x77);
            if (!flags.ContainsKey(flag))
            {
                flags.Add(flag, new());
            }
            flags[flag].replaces.Add(buffer.Count);
            flags[flag].calcs.Add(buffer.Count + 1);
            flags[flag].sizes.Add(1);
            buffer.Add(0);
        }
        internal void mov_ecx(int value)
        {
            buffer.AddRange(new byte[] { 0x8B, 0x0D });
            buffer.AddRange(BitConverter.GetBytes(value));
        }

        internal void mov_eax_ptr(int value)
        {
            buffer.Add(0xA1);
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void lea_ecx_ecx(int value)
        {
            buffer.AddRange(new byte[] { 0x8D, 0x89 });
            buffer.AddRange(BitConverter.GetBytes(value));
        }

        internal void lea_ecx_eax(int value)
        {
            buffer.AddRange(new byte[] { 0x8D, 0x88 });
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void add_ecx_esi()
        {
            buffer.AddRange(new byte[] { 0x03, 0xCE });
        }
        internal void add_esi(int value)
        {
            buffer.AddRange(new byte[] { 0x81, 0xC6 });
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void inc_edi()
        {
            buffer.Add(0x47);

        }
        internal void cmp_esi(int value)
        {
            buffer.AddRange(new byte[] { 0x81, 0xFE });
            buffer.AddRange(BitConverter.GetBytes(value));
        }

        internal void lea_ecx_esi(int value)
        {
            buffer.AddRange(new byte[] { 0x8D, 0x8E });
            buffer.AddRange(BitConverter.GetBytes(value));
        }
        internal void nop()
        {
            buffer.Add(0x90);
        }
        internal void jmp(int value)
        {
            buffer.Add(0xE9);//jmp
            buffer.AddRange(BitConverter.GetBytes(value - pMem - buffer.Count - 4));
        }
        internal void call(int value)
        {
            buffer.Add(0xE8);
            buffer.AddRange(BitConverter.GetBytes(value - pMem - buffer.Count - 4));
        }
        internal void mov_byte_ptr(int value, byte value2)
        {
            buffer.AddRange(new byte[] { 0xC6, 0x05 });
            buffer.AddRange(BitConverter.GetBytes(value));
            buffer.Add(value2);
        }


        internal void cmp_byte_ptr(int address, byte value)
        {
            buffer.AddRange(new byte[] { 0x80, 0x3D });
            buffer.AddRange(BitConverter.GetBytes(address));
            buffer.Add(value);//0
        }
    }

}
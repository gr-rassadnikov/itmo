
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include<map>


using namespace std;

#define uint unsigned int

#define b7 bitset <7>
#define b3 bitset <3>

//Checkers----------------------------
ifstream input;
FILE *pFile;
vector<unsigned char> in;

void open_files(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "please write input and output file name\n";
        exit(0);
    }
    input.open(argv[1]);
    pFile = fopen(argv[2], "w");
    if (!input) {
        cout << "failed to find input file\n";
        exit(0);
    }
    if (!pFile) {
        cout << "failed to find output file\n";
        exit(0);
    }
}

void read_in() {
    char e;
    while (input.get(e)) {
        in.push_back(e);
    }
}

void check_ELF_file() {
    if (in[1] != 0x45 || in[2] != 0x4c || in[3] != 0x46) {
        cout << "it isn't ELF file\n";
        exit(0);
    }

}

void check_ARM32() {
    if (in[4] != 0x01) {
        cout << "it isn't ELF32\n";
        exit(0);
    }

}

void check_LE() {
    if (in[5] != 0x01) {
        cout << "it isn't little - endian\n";
        exit(0);
    }

}

void check_RISCV() {
    if (in[18] != 0xf3) {
        cout << "it isn't RISC-V\n";
        exit(0);
    }
}

//----------------------------------


//converters-----------------------
unsigned int convert_4(uint a1, uint a2, uint a3, uint a4) {
    return a1 + a2 * 256 + a3 * 256 * 256 + a4 * 256 * 256 * 256;
}

unsigned int convert_2(uint a1, uint a2) {
    return a1 + a2 * 256;
}
//---------------------------------


//Binary---------------------------

uint offset_for_str(uint u_id, uint e_shoff, uint e_shstrndx) {
    int u_offset = 0;

    for (uint i = e_shoff; i < e_shoff + 40 * e_shstrndx + 40; i += 40) {
        uint value_in_line = convert_4(in[i], in[i + 1], in[i + 2], in[i + 3]);
        if (value_in_line == u_id) {
            u_offset = convert_4(in[i + 16], in[i + 17], in[i + 18], in[i + 19]);
            return u_offset;

        }

    }
    return u_offset;
}

uint size_for_str(uint u_id, uint e_shoff, uint e_shstrndx) {
    int u_offset = 0;

    for (uint i = e_shoff; i < e_shoff + 40 * e_shstrndx + 40; i += 40) {
        uint value_in_line = convert_4(in[i], in[i + 1], in[i + 2], in[i + 3]);
        if (value_in_line == u_id) {
            u_offset = convert_4(in[i + 16 + 4], in[i + 17 + 4], in[i + 18 + 4], in[i + 19 + 4]);
            return u_offset;

        }

    }
    return u_offset;
}

uint adress_for_str(uint u_id, uint e_shoff, uint e_shstrndx) {
    int u_offset = 0;

    for (uint i = e_shoff; i < e_shoff + 40 * e_shstrndx + 40; i += 40) {
        uint value_in_line = convert_4(in[i], in[i + 1], in[i + 2], in[i + 3]);
        if (value_in_line == u_id) {
            u_offset = convert_4(in[i + 8 + 4], in[i + 8 + 4 + 1], in[i + 4 + 8 + 2], in[i + 4 + 8 + 3]);
            return u_offset;

        }

    }
    return u_offset;
}

unsigned int id_for_str(string find, uint sh_offset, uint sh_size) {
    string s = "";
    for (uint i = sh_offset; i < sh_offset + sh_size; i++) {

        if (in[i] != '\0') {
            s += in[i];

        } else {
            if (s == find) {
                return i - sh_offset - find.size();
            } else {
                s = "";
            }
        }
    }
    return 0;

}


//----------------------------------


//Symtab ------------------------------------


struct symtab {
    uint st_name; //0...3
    uint st_value;// 4...7
    uint st_size;// 8...11
    uint st_info;// 12
    uint st_other;//13
    uint st_shndex;// 14,15
    string st_name_convert;
};
vector<symtab> table;

string name_for_symtab(uint from) {
    string s = "";
    for (uint i = from; i < from + 40; i++) {
        if (in[i] != '\0') {
            s += in[i];

        } else {
            return s;
        }
    }
    return s;

}

string get_type_symtab(uint i) {
    if (i == 0x0) { return "NONTYPE"; }
    else if (i == 0x1) { return "OBJECT"; }
    else if (i == 0x2) { return "FUNC"; }
    else if (i == 0x3) { return "SECTION"; }
    else if (i == 0x4) { return "FILE"; }
    else if (i == 0x13) { return "LOPROC"; }
    else if (i == 0x15) { return "HIPROC"; }
    else { return "unknown_command"; }
}

string get_bind_symtab(uint i) {
    if (i == 0x0) { return "LOCAL"; }
    else if (i == 0x1) { return "GLOBAL"; }
    else if (i == 0x2) { return "WEAK"; }
    else if (i == 0x3) { return "SECTION"; }
    else if (i == 0x4) { return "FILE"; }
    else if (i == 0x13) { return "LOPROC"; }
    else if (i == 0x15) { return "HIPROC"; }
    else { return "unknown_command"; }
}

string get_vis_symtab(uint i) {
    if (i == 0x0) { return "DEFAULT"; }
    else if (i == 0x1) { return "INTERNAL"; }
    else if (i == 0x2) { return "HIDDEN"; }
    else if (i == 0x3) { return "PROTECTED"; }
    else { return "unknown_command"; }
}

string get_index_symtab(uint i) {
    if (i == 0x0) { return "UNDEF"; }
    else if (i == 0xff00) { return "SHN_BEFORE"; }
    else if (i == 0xff01) { return "AFTER"; }
    else if (i == 0xff1f) { return "HIPROC"; }
    else if (i == 0xfff2) { return "COMMON"; }
    else if (i == 0xfff1) { return "ABS"; }
    else if (i == 0xffff) { return "HIRESERVE"; }
    else { return to_string(i); }
}

void parse_save_symtab(uint symtab_offset, uint symtab_size, uint strtab_offset) {
    for (int i = symtab_offset; i < symtab_offset + symtab_size; i += 16) {
        symtab symtab;
        symtab.st_name = convert_4(in[i], in[i + 1], in[i + 2], in[i + 3]);
        symtab.st_value = convert_4(in[i + 4], in[i + 1 + 4], in[i + 2 + 4], in[i + 3 + 4]);
        symtab.st_size = convert_4(in[i + 4 + 4], in[i + 1 + 4 + 4], in[i + 2 + 4 + 4], in[i + 3 + 4 + 4]);
        symtab.st_info = in[i + 12];
        symtab.st_other = in[i + 13];
        symtab.st_shndex = convert_2(in[i + 14], in[i + 15]);
        symtab.st_name_convert = name_for_symtab(strtab_offset + symtab.st_name).c_str();
        table.push_back(symtab);


    }
}

void print_symtab(uint symtab_offset, uint symtab_size, uint strtab_offset) {

    fprintf(pFile, ".symtab\n");
    int number = 0;
    fprintf(pFile, "%s %-15s %7s %-8s %-8s %-8s %6s %s\n",
            "Symbol", "Value", "Size", "Type", "Bind", "Vis", "Index", "Name");
    for (symtab i: table) {
        fprintf(pFile, "[%4i] 0x%-15X %5i %-8s %-8s %-8s %6s %s\n",
                number,
                i.st_value,
                i.st_size,
                get_type_symtab(i.st_info % 16).c_str(),
                get_bind_symtab(i.st_info / 16).c_str(),
                get_vis_symtab(i.st_other).c_str(),
                get_index_symtab(i.st_shndex).c_str(),
                name_for_symtab(strtab_offset + i.st_name).c_str()
        );
        number++;
    }
}


//-----------------------------------


uint to_uint(string s) {
    uint mn = 1;
    uint ans = 0;
    for (uint i = 0; i < s.length(); i++) {
        if (s[i] == '1') {
            ans += mn;
        }
        mn *= 2;
    }
    return ans;
}

int to_int(string s) {
    int mn = 1;
    int ans = 0;

    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '1') {
            ans += mn;
        }
        mn *= 2;
    }
    if (s[s.length() - 1] == '1') {
        ans -= mn;
    }
    return ans;
}


bitset<7> slice_0_6(bitset<32> c) {
    bitset<7> get(to_string(c[0]) + to_string(c[1]) +
                  to_string(c[2]) + to_string(c[3]) +
                  to_string(c[4]) + to_string(c[5]) + to_string(c[6]));
    return get;

}

string slice_7_11(bitset<32> c) {
    string get = to_string(c[7]) + to_string(c[8]) +
                 to_string(c[9]) + to_string(c[10]) +
                 to_string(c[11]);
    return get;

}

string slice_12_14(bitset<32> c) {
    string get = to_string(c[12]) + to_string(c[13]) +
                 to_string(c[14]);
    return get;

}

string slice_12_31(bitset<32> c) {
    string get;
    for (int i = 12; i < 32; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_0_11(bitset<32> c) {
    string get;
    for (int i = 0; i < 12; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_15_19(bitset<32> c) {
    string get;
    for (int i = 15; i < 20; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_5_10(bitset<32> c) {
    string get;
    for (int i = 5; i < 11; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_1_4(bitset<32> c) {
    string get;
    for (int i = 1; i < 5; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_20_24(bitset<32> c) {
    string get;
    for (int i = 20; i < 25; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_5_11(bitset<32> c) {
    string get;
    for (int i = 5; i < 12; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_0_4(bitset<32> c) {
    string get;
    for (int i = 0; i < 5; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string slice_25_31(bitset<32> c) {
    string get;
    for (int i = 25; i < 32; i++) {
        get += to_string(c[i]);
    }
    return get;

}

string hex(int x) {
    string s = "";
    while (x > 0) {
        string ne = to_string(x % 16);
        if (ne == "10") {
            ne = "a";
        }
        if (ne == "11") {
            ne = "b";
        }
        if (ne == "12") {
            ne = "c";
        }
        if (ne == "13") {
            ne = "d";
        }
        if (ne == "14") {
            ne = "e";
        }
        if (ne == "15") {
            ne = "f";
        }
        s += ne;

        x = x / 16;
    }
    if (s == "") {
        return "0";
    }
    return s;
}

string convert_rd(uint rd) {
    if (rd == 0)return "zero";
    else if (rd == 1) return "ra";
    else if (rd == 2) return "sp";
    else if (rd == 3) return "gp";
    else if (rd == 4) return "tp";
    else if (rd == 5) return "t0";
    else if (rd == 6) return "t1";
    else if (rd == 7) return "t2";
    else if (rd == 8) return "s0";
    else if (rd == 9) return "s1";
    else if (rd == 10) return "a0";
    else if (rd == 11) return "a1";
    else if (rd == 12) return "a2";
    else if (rd == 13) return "a3";
    else if (rd == 14) return "a4";
    else if (rd == 15) return "a5";
    else if (rd == 16) return "a6";
    else if (rd == 17) return "a7";
    else if (rd == 18) return "s2";
    else if (rd == 19) return "s3";
    else if (rd == 20) return "s4";
    else if (rd == 21) return "s5";
    else if (rd == 22) return "s6";
    else if (rd == 23) return "s7";
    else if (rd == 24) return "s8";
    else if (rd == 25) return "s9";
    else if (rd == 26) return "s10";
    else if (rd == 27) return "s11";
    else if (rd == 28) return "t3";
    else if (rd == 29) return "t4";
    else if (rd == 30) return "t5";
    else if (rd == 31) return "t6";
    return "unknown";
}

struct st {
    string name = "";
    uint rd = -1;
    int imm = -1;
    uint rs1 = -1;
    uint rs2 = -1;
    string imm_str = "";
};

st parse_i_type(bitset<32> c) {
    st st;
    st.rd = to_uint(slice_7_11(c));
    st.rs1 = to_uint(slice_15_19(c));
    string s;
    for (int i = 20; i <= 31; i++) {
        s += to_string(c[i]);
    }
    st.imm = to_int(s);
    return st;
}

st parse_b_type(bitset<32> c) {
    st st;

    st.rs1 = to_uint(slice_15_19(c));
    st.rs2 = to_uint(slice_20_24(c));
    string s = "0000000000000";
    s[11] = (char) (c[7] + '0');

    for (int i = 8; i <= 11; i++) {
        s[i - 7] = (char) (c[i] + '0');
    }
    for (int i = 25; i <= 30; i++) {
        s[i - 20] = (char) (c[i] + '0');
    }
    s[12] = c[31];

    st.imm = to_int(s);
    return st;
}

st parse_s_type(bitset<32> c) {
    st st;

    st.rs1 = to_uint(slice_15_19(c));
    st.rs2 = to_uint(slice_20_24(c));
    string s = "000000000000";
    for (int i = 7; i <= 11; i++) {
        s[i - 7] = (char) (c[i] + '0');
    }
    for (int i = 25; i <= 31; i++) {
        s[i - 20] = (char) (c[i] + '0');
    }
    st.imm = to_int(s);
    return st;
}

st parse_u_type(bitset<32> c) {
    st st;
    st.rd = to_uint(slice_7_11(c));
    string s = "";
    for (int i = 12; i <= 31; i++) {
        s += to_string(c[i]);
    }
    st.imm = to_int(s);
    return st;
}

st parse_r_type(bitset<32> c) {
    st st;
    st.rd = to_uint(slice_7_11(c));
    st.rs1 = to_uint(slice_15_19(c));
    st.rs2 = to_uint(slice_20_24(c));

    return st;
}

st parse_j_type(bitset<32> c) {
    st st;
    st.rd = to_uint(slice_7_11(c));
    string s = "00000000000000000000";
    for (int i = 12; i <= 19; i++) {
        s[i] = (char) (c[i] + '0');
    }
    s[11] = (char) (c[20] + '0');
    for (int i = 21; i <= 30; i++) {
        s[i - 20] = (char) (c[i] + '0');
    }
    s[20] = c[31];
    st.imm = to_int(s);
    return st;
}

map<int, string> metki;
int loc = 0;

void save_metki(int imm, int adress, string type_st, st &stt) {
    int adress_f = adress + imm;

    for (auto i: table) {
        if (i.st_value == adress_f && i.st_info % 16 == 2) {
            metki[adress_f] = i.st_name_convert;
            stt.imm_str = i.st_name_convert;
            return;
        }
    }
    if (type_st == "b" || type_st == "j") {
        metki[adress_f] = hex(loc);
        string w = "LOC_";
        if (hex(loc).length() == 1) { w += "0000"; }
        if (hex(loc).length() == 2) { w += "000"; }
        if (hex(loc).length() == 3) { w += "00"; }
        if (hex(loc).length() == 4) { w += "0"; }
        w += hex(loc);
        metki[adress_f] = w;
        stt.imm_str = w;
        loc++;
    }

}

vector<st> text;

bitset<32> RV32(bitset<32> c, int adress) {
    bitset<7> c_0_6 = slice_0_6(c);
    st st;
    string type_st = "";

    if (c_0_6 == b7("1110110")) {
        type_st = "u";
        st = parse_u_type(c);
        st.name = "lui";
    } else if (c_0_6 == b7("1110100")) {
        type_st = "u";
        st = parse_u_type(c);
        st.name = "auipc";

    } else if (c_0_6 == b7("1111011")) {
        type_st = "j";
        st = parse_j_type(c);
        st.name = "jal";//-----------------------
    } else if (c_0_6 == b7("1110011") && slice_12_14(c) == "000") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "jalr";
    } else if (c_0_6 == b7("1100011") && slice_12_14(c) == "000") {
        type_st = "b";
        st = parse_b_type(c);
        st.name = "beq";
    } else if (c_0_6 == b7("1100011") && slice_12_14(c) == "100") {
        type_st = "b";
        st = parse_b_type(c);
        st.name = "bne";
    } else if (c_0_6 == b7("1100011") && slice_12_14(c) == "001") {
        type_st = "b";
        st = parse_b_type(c);
        st.name = "blt";
    } else if (c_0_6 == b7("1100011") && slice_12_14(c) == "101") {
        type_st = "b";
        st = parse_b_type(c);
        st.name = "bge";
    } else if (c_0_6 == b7("1100011") && slice_12_14(c) == "011") {
        type_st = "b";
        st = parse_b_type(c);
        st.name = "bltu";
    } else if (c_0_6 == b7("1100011") && slice_12_14(c) == "111") {
        type_st = "b";
        st = parse_b_type(c);
        st.name = "bgeu";
    } else if (c_0_6 == b7("1100000") && slice_12_14(c) == "000") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "lb";
    } else if (c_0_6 == b7("1100000") && slice_12_14(c) == "100") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "lh";
    } else if (c_0_6 == b7("1100000") && slice_12_14(c) == "010") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "lw";
    } else if (c_0_6 == b7("1100000") && slice_12_14(c) == "001") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "lbu";
    } else if (c_0_6 == b7("1100000") && slice_12_14(c) == "101") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "lhu";
    } else if (c_0_6 == b7("1100010") && slice_12_14(c) == "000") {
        type_st = "s";
        st = parse_s_type(c);
        st.name = "sb";
    } else if (c_0_6 == b7("1100010") && slice_12_14(c) == "100") {
        type_st = "s";
        st = parse_s_type(c);
        st.name = "sh";
    } else if (c_0_6 == b7("1100010") && slice_12_14(c) == "010") {
        type_st = "s";
        st = parse_s_type(c);
        st.name = "sw";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "000") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "addi";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "010") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "slti";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "110") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "sltiu";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "001") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "xori";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "011") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "ori";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "111") {
        type_st = "i";
        st = parse_i_type(c);
        st.name = "andi";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "100"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "slli";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "101"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "srli";
    } else if (c_0_6 == b7("1100100") && slice_12_14(c) == "100"
               && slice_25_31(c) == "0000010") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "srai";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "000"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "add";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "000"
               && slice_25_31(c) == "0000010") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "sub";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "100"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "sll";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "010"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "slt";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "110"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "slt";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "001"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "xor";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "101"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "srl";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "101"
               && slice_25_31(c) == "0000010") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "sra";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "011"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "or";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "111"
               && slice_25_31(c) == "0000000") {
        type_st = "r";
        st = parse_r_type(c);
        st.name = "and";
    } else if (c_0_6 == b7("1100111") && c[20] == 0) {
        type_st = "0";
        st.name = "ecall";
    } else if (c_0_6 == b7("1100111") && c[20] == 1) {
        st.name = "ebreak";
        type_st = "0";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "000"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "mul";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "100"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "mulh";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "010"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "mulhsu";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "110"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "mulhu";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "001"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "div";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "101"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "divu";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "011"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "rem";
        type_st = "r";
    } else if (c_0_6 == b7("1100110") && slice_12_14(c) == "111"
               && slice_25_31(c) == "1000000") {
        st = parse_r_type(c);
        st.name = "remu";
        type_st = "r";
    } else {
        st.name = "unknown_command";
        type_st = "0";
    }

    save_metki(st.imm, adress, type_st, st);

    text.push_back(st);
    return c;
}

void print_RV32(st stt) {

    if (stt.name != "") {
        //printf(" %s", stt.name.c_str());
        fprintf(pFile, " %s", stt.name.c_str());
    }
    if (stt.rd != -1) {
        //printf(" %s,", convert_rd(stt.rd).c_str());
        fprintf(pFile, " %s,", convert_rd(stt.rd).c_str());
    }
    if (stt.rs1 != -1) {
        //printf(" %s,", convert_rd(stt.rs1).c_str());
        fprintf(pFile, " %s,", convert_rd(stt.rs1).c_str());
    }
    if (stt.rs2 != -1) {
        //printf(" %s,", convert_rd(stt.rs2).c_str());
        fprintf(pFile, " %s,", convert_rd(stt.rs2).c_str());
    }
    if (stt.imm != -1) {
        if (stt.imm_str != "") {
            //printf(" %s", stt.imm_str.c_str());
            fprintf(pFile, " %s", stt.imm_str.c_str());
        } else {
            //printf(" %s", to_string(stt.imm).c_str());
            fprintf(pFile, " %s", to_string(stt.imm).c_str());
        }

    }
    //printf("\n");
    fprintf(pFile, "\n");


}

void parse_text(uint text_offset, uint text_size, uint text_adress) {
    for (uint i = text_offset; i < text_offset + text_size; i++) {
        bitset<8> byte = in[i];
        if (byte[0] == byte[1] == 1) {
            bitset<32> command = convert_4(in[i], in[i + 1], in[i + 2], in[i + 3]);
            RV32(command, i - text_offset + text_adress);

            i += 3;
        } else {
            i += 1;
        }

    }


}

void print_text(uint text_offset, uint text_size, uint text_adress) {
    fprintf(pFile, ".text\n");
    int ind = 0;
    for (uint i = text_offset; i < text_offset + text_size; i++) {
        string metka = "";
        if (metki.count(i - text_offset + text_adress) == 1) {
            metka = metki[i - text_offset + text_adress] + ":";
        }
        fprintf(pFile, "%08x %10s", i - text_offset + text_adress,
                metka.c_str());
        bitset<8> byte = in[i];
        if (byte[0] == byte[1] == 1) {
            bitset<32> command = convert_4(in[i], in[i + 1], in[i + 2], in[i + 3]);
            print_RV32(text[ind++]);
            i += 3;
        } else {
            i += 1;
        }

    }
}


int main(int argc, char *argv[]) {
    open_files(argc, argv);
    read_in();
    check_ELF_file();
    check_ARM32();
    check_LE();
    check_RISCV();


    unsigned int e_shoff = convert_4(in[32], in[33], in[34], in[35]);
    unsigned int e_shnum = convert_2(in[48], in[49]);
    unsigned int e_shstrndx = convert_2(in[50], in[51]);
    unsigned int shstrtab = e_shoff + 40 * e_shstrndx;
    unsigned int sh_offset = convert_4(in[shstrtab + 16], in[shstrtab + 17],
                                       in[shstrtab + 18], in[shstrtab + 19]);
    unsigned int sh_size = convert_4(in[shstrtab + 16 + 4], in[shstrtab + 17 + 4], in[shstrtab + 18 + 4],
                                     in[shstrtab + 19 + 4]);
    uint text_id = id_for_str(".text", sh_offset, sh_size);
    uint symtab_id = id_for_str(".symtab", sh_offset, sh_size);
    uint strtab_id = id_for_str(".strtab", sh_offset, sh_size);
    uint text_offset = offset_for_str(text_id, e_shoff, e_shstrndx);
    uint symtab_offset = offset_for_str(symtab_id, e_shoff, e_shstrndx);
    uint strtab_offset = offset_for_str(strtab_id, e_shoff, e_shstrndx);
    uint symtab_size = size_for_str(symtab_id, e_shoff, e_shstrndx);
    uint text_size = size_for_str(text_id, e_shoff, e_shstrndx);
    uint text_adress = adress_for_str(text_id, e_shoff, e_shstrndx);

    parse_save_symtab(symtab_offset, symtab_size, strtab_offset);
    parse_text(text_offset, text_size, text_adress);
    print_text(text_offset, text_size, text_adress);
    fprintf(pFile, "\n");
    print_symtab(symtab_offset, symtab_size, strtab_offset);

    input.close();
    fclose(pFile);
    return 0;


}
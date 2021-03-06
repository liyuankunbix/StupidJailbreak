//
//  insn.hpp
//  liboffsetfinder64
//
//  Created by tihmstar on 09.03.18.
//  Copyright © 2018 tihmstar. All rights reserved.
//

#ifndef insn_hpp
#define insn_hpp

#include <liboffsetfinder64/common.h>
#include <vector>

namespace tihmstar{
    namespace patchfinder64{
        class insn{
        public:
            enum segtype{
                kText_only,
                kData_only,
                kText_and_Data
            };
        private:
            std::pair <loc_t,int> _p;
            std::vector<text_t> _segments;
            segtype _segtype;
        public:
            insn(segment_t segments, loc_t p = 0, segtype segType = kText_only);
            insn(const insn &cpy, loc_t p=0);
            insn &operator++();
            insn &operator--();
            insn operator+(int i);
            insn operator-(int i);
            insn &operator+=(int i);
            insn &operator-=(int i);
            insn &operator=(loc_t p);
            
        public: //helpers
            uint64_t pc();
            uint32_t value();
            uint64_t doublevalue();
            
        public: //static type determinition
            static uint64_t deref(segment_t segments, loc_t p);
            static bool is_adrp(uint32_t i);
            static bool is_adr(uint32_t i);
            static bool is_add(uint32_t i);
            static bool is_bl(uint32_t i);
            static bool is_cbz(uint32_t i);
            static bool is_ret(uint32_t i);
            static bool is_tbnz(uint32_t i);
            static bool is_br(uint32_t i);
            static bool is_ldr(uint32_t i);
            static bool is_cbnz(uint32_t i);
            static bool is_movk(uint32_t i);
            static bool is_orr(uint32_t i);
            static bool is_tbz(uint32_t i);
            static bool is_ldxr(uint32_t i);
            static bool is_ldrb(uint32_t i);
            static bool is_str(uint32_t i);
            static bool is_stp(uint32_t i);
            static bool is_movz(uint32_t i);
            static bool is_bcond(uint32_t i);
            static bool is_b(uint32_t i);
            static bool is_nop(uint32_t i);
            
        public: //type
            enum type{
                unknown,
                adrp,
                adr,
                bl,
                cbz,
                ret,
                tbnz,
                add,
                br,
                ldr,
                cbnz,
                movk,
                orr,
                tbz,
                ldxr,
                ldrb,
                str,
                stp,
                movz,
                bcond,
                b,
                nop
            };
            enum subtype{
                st_general,
                st_register,
                st_immediate,
                st_literal
            };
            enum supertype{
                sut_general,
                sut_branch_imm
            };
            enum cond{
                NE = 000,
                EG = 000,
                CS = 001,
                CC = 001,
                MI = 010,
                PL = 010,
                VS = 011,
                VC = 011,
                HI = 100,
                LS = 100,
                GE = 101,
                LT = 101,
                GT = 110,
                LE = 110,
                AL = 111
            };
            type type();
            subtype subtype();
            supertype supertype();
            int64_t imm();
            uint8_t rd();
            uint8_t rn();
            uint8_t rt();
            uint8_t other();
        public: //cast operators
            operator void*();
            operator loc_t();
            operator enum type();
        };
        
        loc_t find_literal_ref(segment_t segemts, loc_t pos);
        loc_t find_rel_branch_source(insn bdst, bool searchUp, int ignoreTimes=0, int limit = 0);
        
    };
};


#endif /* insn_hpp */


const PinIdToPortTranslation PinIdToPort[]={
    { PORTTYPE_NOT_CONFIGURABLE, 0, 0}, /*The PIN list starts at 1 */
    { PORTTYPE_AP              ,  0,  0 }, /* Pin:1   Name:AP0_0      */
    { PORTTYPE_AP              ,  0,  1 }, /* Pin:2   Name:AP0_1      */
    { PORTTYPE_AP              ,  0,  2 }, /* Pin:3   Name:AP0_2      */
    { PORTTYPE_AP              ,  0,  3 }, /* Pin:4   Name:AP0_3      */
    { PORTTYPE_AP              ,  0,  4 }, /* Pin:5   Name:AP0_4      */
    { PORTTYPE_AP              ,  0,  5 }, /* Pin:6   Name:AP0_5      */
    { PORTTYPE_AP              ,  0,  6 }, /* Pin:7   Name:AP0_6      */
    { PORTTYPE_AP              ,  0,  7 }, /* Pin:8   Name:AP0_7      */
    { PORTTYPE_AP              ,  0,  8 }, /* Pin:9   Name:AP0_8      */
    { PORTTYPE_AP              ,  0,  9 }, /* Pin:10  Name:AP0_9      */
    { PORTTYPE_AP              ,  0, 10 }, /* Pin:11  Name:AP0_10     */
    { PORTTYPE_AP              ,  0, 11 }, /* Pin:12  Name:AP0_11     */
    { PORTTYPE_AP              ,  0, 12 }, /* Pin:13  Name:AP0_12     */
    { PORTTYPE_AP              ,  0, 13 }, /* Pin:14  Name:AP0_13     */
    { PORTTYPE_AP              ,  0, 14 }, /* Pin:15  Name:AP0_14     */
    { PORTTYPE_AP              ,  0, 15 }, /* Pin:16  Name:AP0_15     */
    { PORTTYPE_AP              ,  1,  0 }, /* Pin:17  Name:AP1_0      */
    { PORTTYPE_AP              ,  1,  1 }, /* Pin:18  Name:AP1_1      */
    { PORTTYPE_AP              ,  1,  2 }, /* Pin:19  Name:AP1_2      */
    { PORTTYPE_AP              ,  1,  3 }, /* Pin:20  Name:AP1_3      */
    { PORTTYPE_AP              ,  1,  4 }, /* Pin:21  Name:AP1_4      */
    { PORTTYPE_AP              ,  1,  5 }, /* Pin:22  Name:AP1_5      */
    { PORTTYPE_AP              ,  1,  6 }, /* Pin:23  Name:AP1_6      */
    { PORTTYPE_AP              ,  1,  7 }, /* Pin:24  Name:AP1_7      */
    { PORTTYPE_AP              ,  1,  8 }, /* Pin:25  Name:AP1_8      */
    { PORTTYPE_AP              ,  1,  9 }, /* Pin:26  Name:AP1_9      */
    { PORTTYPE_AP              ,  1, 10 }, /* Pin:27  Name:AP1_10     */
    { PORTTYPE_AP              ,  1, 11 }, /* Pin:28  Name:AP1_11     */
    { PORTTYPE_AP              ,  1, 12 }, /* Pin:29  Name:AP1_12     */
    { PORTTYPE_AP              ,  1, 13 }, /* Pin:30  Name:AP1_13     */
    { PORTTYPE_AP              ,  1, 14 }, /* Pin:31  Name:AP1_14     */
    { PORTTYPE_AP              ,  1, 15 }, /* Pin:32  Name:AP1_15     */
    { PORTTYPE_JP              ,  0,  0 }, /* Pin:33  Name:JP0_0      */
    { PORTTYPE_JP              ,  0,  1 }, /* Pin:34  Name:JP0_1      */
    { PORTTYPE_JP              ,  0,  2 }, /* Pin:35  Name:JP0_2      */
    { PORTTYPE_JP              ,  0,  3 }, /* Pin:36  Name:JP0_3      */
    { PORTTYPE_JP              ,  0,  4 }, /* Pin:37  Name:JP0_4 (*18) */
    { PORTTYPE_JP              ,  0,  5 }, /* Pin:38  Name:JP0_5      */
    { PORTTYPE_JP              ,  0,  6 }, /* Pin:39  Name:JP0_6      */
    { PORTTYPE_P               ,  0,  0 }, /* Pin:40  Name:P0_0       */
    { PORTTYPE_P               ,  0,  1 }, /* Pin:41  Name:P0_1       */
    { PORTTYPE_P               ,  0,  2 }, /* Pin:42  Name:P0_2       */
    { PORTTYPE_P               ,  0,  3 }, /* Pin:43  Name:P0_3       */
    { PORTTYPE_P               ,  0,  4 }, /* Pin:44  Name:P0_4       */
    { PORTTYPE_P               ,  0,  5 }, /* Pin:45  Name:P0_5       */
    { PORTTYPE_P               ,  0,  6 }, /* Pin:46  Name:P0_6       */
    { PORTTYPE_P               ,  0,  7 }, /* Pin:47  Name:P0_7       */
    { PORTTYPE_P               ,  0,  8 }, /* Pin:48  Name:P0_8       */
    { PORTTYPE_P               ,  0,  9 }, /* Pin:49  Name:P0_9       */
    { PORTTYPE_P               ,  0, 10 }, /* Pin:50  Name:P0_10      */
    { PORTTYPE_P               ,  0, 11 }, /* Pin:51  Name:P0_11      */
    { PORTTYPE_P               ,  0, 12 }, /* Pin:52  Name:P0_12      */
    { PORTTYPE_P               ,  0, 13 }, /* Pin:53  Name:P0_13      */
    { PORTTYPE_P               ,  0, 14 }, /* Pin:54  Name:P0_14      */
    { PORTTYPE_P               ,  1,  0 }, /* Pin:55  Name:P1_0       */
    { PORTTYPE_P               ,  1,  1 }, /* Pin:56  Name:P1_1       */
    { PORTTYPE_P               ,  1,  2 }, /* Pin:57  Name:P1_2       */
    { PORTTYPE_P               ,  1,  3 }, /* Pin:58  Name:P1_3       */
    { PORTTYPE_P               ,  1,  4 }, /* Pin:59  Name:P1_4       */
    { PORTTYPE_P               ,  1,  5 }, /* Pin:60  Name:P1_5       */
    { PORTTYPE_P               ,  1,  6 }, /* Pin:61  Name:P1_6       */
    { PORTTYPE_P               ,  1,  7 }, /* Pin:62  Name:P1_7       */
    { PORTTYPE_P               ,  1,  8 }, /* Pin:63  Name:P1_8       */
    { PORTTYPE_P               ,  1,  9 }, /* Pin:64  Name:P1_9       */
    { PORTTYPE_P               ,  1, 10 }, /* Pin:65  Name:P1_10      */
    { PORTTYPE_P               ,  1, 11 }, /* Pin:66  Name:P1_11      */
    { PORTTYPE_P               ,  1, 12 }, /* Pin:67  Name:P1_12      */
    { PORTTYPE_P               ,  1, 13 }, /* Pin:68  Name:P1_13      */
    { PORTTYPE_P               ,  1, 14 }, /* Pin:69  Name:P1_14      */
    { PORTTYPE_P               ,  1, 15 }, /* Pin:70  Name:P1_15      */
    { PORTTYPE_P               ,  2,  0 }, /* Pin:71  Name:P2_0       */
    { PORTTYPE_P               ,  2,  1 }, /* Pin:72  Name:P2_1       */
    { PORTTYPE_P               ,  2,  2 }, /* Pin:73  Name:P2_2       */
    { PORTTYPE_P               ,  2,  3 }, /* Pin:74  Name:P2_3       */
    { PORTTYPE_P               ,  2,  4 }, /* Pin:75  Name:P2_4       */
    { PORTTYPE_P               ,  2,  5 }, /* Pin:76  Name:P2_5       */
    { PORTTYPE_P               ,  2,  6 }, /* Pin:77  Name:P2_6       */
    { PORTTYPE_P               ,  2,  7 }, /* Pin:78  Name:P2_7       */
    { PORTTYPE_P               ,  2,  8 }, /* Pin:79  Name:P2_8       */
    { PORTTYPE_P               ,  2,  9 }, /* Pin:80  Name:P2_9       */
    { PORTTYPE_P               ,  2, 10 }, /* Pin:81  Name:P2_10      */
    { PORTTYPE_P               ,  2, 11 }, /* Pin:82  Name:P2_11      */
    { PORTTYPE_P               ,  2, 12 }, /* Pin:83  Name:P2_12      */
    { PORTTYPE_P               ,  2, 13 }, /* Pin:84  Name:P2_13      */
    { PORTTYPE_P               ,  2, 14 }, /* Pin:85  Name:P2_14      */
    { PORTTYPE_P               ,  2, 15 }, /* Pin:86  Name:P2_15      */
    { PORTTYPE_P               ,  3,  0 }, /* Pin:87  Name:P3_0       */
    { PORTTYPE_P               ,  3,  1 }, /* Pin:88  Name:P3_1       */
    { PORTTYPE_P               ,  3,  2 }, /* Pin:89  Name:P3_2       */
    { PORTTYPE_P               ,  3,  3 }, /* Pin:90  Name:P3_3       */
    { PORTTYPE_P               ,  3,  4 }, /* Pin:91  Name:P3_4       */
    { PORTTYPE_P               ,  3,  5 }, /* Pin:92  Name:P3_5       */
    { PORTTYPE_P               ,  3,  6 }, /* Pin:93  Name:P3_6       */
    { PORTTYPE_P               ,  3,  7 }, /* Pin:94  Name:P3_7       */
    { PORTTYPE_P               ,  3,  8 }, /* Pin:95  Name:P3_8       */
    { PORTTYPE_P               ,  3,  9 }, /* Pin:96  Name:P3_9       */
    { PORTTYPE_P               ,  3, 10 }, /* Pin:97  Name:P3_10      */
    { PORTTYPE_P               ,  8,  0 }, /* Pin:98  Name:P8_0       */
    { PORTTYPE_P               ,  8,  1 }, /* Pin:99  Name:P8_1       */
    { PORTTYPE_P               ,  8,  2 }, /* Pin:100 Name:P8_2       */
    { PORTTYPE_P               ,  8,  3 }, /* Pin:101 Name:P8_3       */
    { PORTTYPE_P               ,  8,  4 }, /* Pin:102 Name:P8_4       */
    { PORTTYPE_P               ,  8,  5 }, /* Pin:103 Name:P8_5       */
    { PORTTYPE_P               ,  8,  6 }, /* Pin:104 Name:P8_6       */
    { PORTTYPE_P               ,  8,  7 }, /* Pin:105 Name:P8_7       */
    { PORTTYPE_P               ,  8,  8 }, /* Pin:106 Name:P8_8       */
    { PORTTYPE_P               ,  8,  9 }, /* Pin:107 Name:P8_9       */
    { PORTTYPE_P               ,  8, 10 }, /* Pin:108 Name:P8_10      */
    { PORTTYPE_P               ,  8, 11 }, /* Pin:109 Name:P8_11      */
    { PORTTYPE_P               ,  8, 12 }, /* Pin:110 Name:P8_12      */
    { PORTTYPE_P               ,  9,  0 }, /* Pin:111 Name:P9_0       */
    { PORTTYPE_P               ,  9,  1 }, /* Pin:112 Name:P9_1       */
    { PORTTYPE_P               ,  9,  2 }, /* Pin:113 Name:P9_2       */
    { PORTTYPE_P               ,  9,  3 }, /* Pin:114 Name:P9_3       */
    { PORTTYPE_P               ,  9,  4 }, /* Pin:115 Name:P9_4       */
    { PORTTYPE_P               ,  9,  5 }, /* Pin:116 Name:P9_5       */
    { PORTTYPE_P               ,  9,  6 }, /* Pin:117 Name:P9_6       */
    { PORTTYPE_P               , 10,  0 }, /* Pin:118 Name:P10_0      */
    { PORTTYPE_P               , 10,  1 }, /* Pin:119 Name:P10_1      */
    { PORTTYPE_P               , 10,  2 }, /* Pin:120 Name:P10_2      */
    { PORTTYPE_P               , 10,  3 }, /* Pin:121 Name:P10_3      */
    { PORTTYPE_P               , 10,  4 }, /* Pin:122 Name:P10_4      */
    { PORTTYPE_P               , 10,  5 }, /* Pin:123 Name:P10_5      */
    { PORTTYPE_P               , 10,  6 }, /* Pin:124 Name:P10_6      */
    { PORTTYPE_P               , 10,  7 }, /* Pin:125 Name:P10_7      */
    { PORTTYPE_P               , 10,  8 }, /* Pin:126 Name:P10_8      */
    { PORTTYPE_P               , 10,  9 }, /* Pin:127 Name:P10_9      */
    { PORTTYPE_P               , 10, 10 }, /* Pin:128 Name:P10_10     */
    { PORTTYPE_P               , 10, 11 }, /* Pin:129 Name:P10_11     */
    { PORTTYPE_P               , 10, 12 }, /* Pin:130 Name:P10_12     */
    { PORTTYPE_P               , 10, 13 }, /* Pin:131 Name:P10_13     */
    { PORTTYPE_P               , 10, 14 }, /* Pin:132 Name:P10_14     */
    { PORTTYPE_P               , 10, 15 }, /* Pin:133 Name:P10_15     */
    { PORTTYPE_P               , 11,  0 }, /* Pin:134 Name:P11_0      */
    { PORTTYPE_P               , 11,  1 }, /* Pin:135 Name:P11_1      */
    { PORTTYPE_P               , 11,  2 }, /* Pin:136 Name:P11_2      */
    { PORTTYPE_P               , 11,  3 }, /* Pin:137 Name:P11_3      */
    { PORTTYPE_P               , 11,  4 }, /* Pin:138 Name:P11_4      */
    { PORTTYPE_P               , 11,  5 }, /* Pin:139 Name:P11_5      */
    { PORTTYPE_P               , 11,  6 }, /* Pin:140 Name:P11_6      */
    { PORTTYPE_P               , 11,  7 }, /* Pin:141 Name:P11_7      */
    { PORTTYPE_P               , 11,  8 }, /* Pin:142 Name:P11_8      */
    { PORTTYPE_P               , 11,  9 }, /* Pin:143 Name:P11_9      */
    { PORTTYPE_P               , 11, 10 }, /* Pin:144 Name:P11_10     */
    { PORTTYPE_P               , 11, 11 }, /* Pin:145 Name:P11_11     */
    { PORTTYPE_P               , 11, 12 }, /* Pin:146 Name:P11_12     */
    { PORTTYPE_P               , 11, 13 }, /* Pin:147 Name:P11_13     */
    { PORTTYPE_P               , 11, 14 }, /* Pin:148 Name:P11_14     */
    { PORTTYPE_P               , 11, 15 }, /* Pin:149 Name:P11_15     */
    { PORTTYPE_P               , 12,  0 }, /* Pin:150 Name:P12_0      */
    { PORTTYPE_P               , 12,  1 }, /* Pin:151 Name:P12_1      */
    { PORTTYPE_P               , 12,  2 }, /* Pin:152 Name:P12_2      */
    { PORTTYPE_P               , 12,  3 }, /* Pin:153 Name:P12_3      */
    { PORTTYPE_P               , 12,  4 }, /* Pin:154 Name:P12_4      */
    { PORTTYPE_P               , 12,  5 }, /* Pin:155 Name:P12_5      */
    { PORTTYPE_P               , 13,  0 }, /* Pin:156 Name:P13_0      */
    { PORTTYPE_P               , 13,  1 }, /* Pin:157 Name:P13_1      */
    { PORTTYPE_P               , 13,  2 }, /* Pin:158 Name:P13_2      */
    { PORTTYPE_P               , 13,  3 }, /* Pin:159 Name:P13_3      */
    { PORTTYPE_P               , 13,  4 }, /* Pin:160 Name:P13_4      */
    { PORTTYPE_P               , 13,  5 }, /* Pin:161 Name:P13_5      */
    { PORTTYPE_P               , 13,  6 }, /* Pin:162 Name:P13_6      */
    { PORTTYPE_P               , 13,  7 }, /* Pin:163 Name:P13_7      */
    { PORTTYPE_P               , 18,  0 }, /* Pin:164 Name:P18_0      */
    { PORTTYPE_P               , 18,  1 }, /* Pin:165 Name:P18_1      */
    { PORTTYPE_P               , 18,  2 }, /* Pin:166 Name:P18_2      */
    { PORTTYPE_P               , 18,  3 }, /* Pin:167 Name:P18_3      */
    { PORTTYPE_P               , 18,  4 }, /* Pin:168 Name:P18_4      */
    { PORTTYPE_P               , 18,  5 }, /* Pin:169 Name:P18_5      */
    { PORTTYPE_P               , 18,  6 }, /* Pin:170 Name:P18_6      */
    { PORTTYPE_P               , 18,  7 }, /* Pin:171 Name:P18_7      */
    { PORTTYPE_P               , 18,  8 }, /* Pin:172 Name:P18_8      */
    { PORTTYPE_P               , 18,  9 }, /* Pin:173 Name:P18_9      */
    { PORTTYPE_P               , 18, 10 }, /* Pin:174 Name:P18_10     */
    { PORTTYPE_P               , 18, 11 }, /* Pin:175 Name:P18_11     */
    { PORTTYPE_P               , 18, 12 }, /* Pin:176 Name:P18_12     */
    { PORTTYPE_P               , 18, 13 }, /* Pin:177 Name:P18_13     */
    { PORTTYPE_P               , 18, 14 }, /* Pin:178 Name:P18_14     */
    { PORTTYPE_P               , 18, 15 }, /* Pin:179 Name:P18_15     */
    { PORTTYPE_P               , 19,  0 }, /* Pin:180 Name:P19_0      */
    { PORTTYPE_P               , 19,  1 }, /* Pin:181 Name:P19_1      */
    { PORTTYPE_P               , 19,  2 }, /* Pin:182 Name:P19_2      */
    { PORTTYPE_P               , 19,  3 }, /* Pin:183 Name:P19_3      */
    { PORTTYPE_P               , 20,  0 }, /* Pin:184 Name:P20_0      */
    { PORTTYPE_P               , 20,  1 }, /* Pin:185 Name:P20_1      */
    { PORTTYPE_P               , 20,  2 }, /* Pin:186 Name:P20_2      */
    { PORTTYPE_P               , 20,  3 }, /* Pin:187 Name:P20_3      */
    { PORTTYPE_P               , 20,  4 }, /* Pin:188 Name:P20_4      */
    { PORTTYPE_P               , 20,  5 }, /* Pin:189 Name:P20_5      */
    { PORTTYPE_P               , 20,  6 }, /* Pin:190 Name:P20_6      */
    { PORTTYPE_P               , 20,  7 }, /* Pin:191 Name:P20_7      */
    { PORTTYPE_P               , 20,  8 }, /* Pin:192 Name:P20_8      */
    { PORTTYPE_P               , 20,  9 }, /* Pin:193 Name:P20_9      */
    { PORTTYPE_P               , 20, 10 }, /* Pin:194 Name:P20_10     */
    { PORTTYPE_P               , 20, 11 }, /* Pin:195 Name:P20_11     */
    { PORTTYPE_P               , 20, 12 }, /* Pin:196 Name:P20_12     */
    { PORTTYPE_P               , 20, 13 }, /* Pin:197 Name:P20_13     */
    { PORTTYPE_P               , 20, 14 }, /* Pin:198 Name:P20_14     */
    { PORTTYPE_P               , 21,  0 }, /* Pin:199 Name:P21_0      */
    { PORTTYPE_P               , 21,  1 }, /* Pin:200 Name:P21_1      */
    { PORTTYPE_P               , 21,  2 }, /* Pin:201 Name:P21_2      */
    { PORTTYPE_P               , 21,  3 }, /* Pin:202 Name:P21_3      */
    { PORTTYPE_P               , 21,  4 }, /* Pin:203 Name:P21_4      */
    { PORTTYPE_P               , 22,  0 }, /* Pin:204 Name:P22_0      */
    { PORTTYPE_P               , 22,  1 }, /* Pin:205 Name:P22_1      */
    { PORTTYPE_P               , 22,  2 }, /* Pin:206 Name:P22_2      */
    { PORTTYPE_P               , 22,  3 }, /* Pin:207 Name:P22_3      */
    { PORTTYPE_P               , 22,  4 }, /* Pin:208 Name:P22_4      */
    { PORTTYPE_P               , 22,  5 }, /* Pin:209 Name:P22_5      */
    { PORTTYPE_P               , 22,  6 }, /* Pin:210 Name:P22_6      */
    { PORTTYPE_P               , 22,  7 }, /* Pin:211 Name:P22_7      */
    { PORTTYPE_P               , 22,  8 }, /* Pin:212 Name:P22_8      */
    { PORTTYPE_P               , 22,  9 }, /* Pin:213 Name:P22_9      */
    { PORTTYPE_P               , 22, 10 }, /* Pin:214 Name:P22_10     */
    { PORTTYPE_P               , 22, 11 }, /* Pin:215 Name:P22_11     */
    { PORTTYPE_P               , 22, 12 }, /* Pin:216 Name:P22_12     */
    { PORTTYPE_P               , 22, 13 }, /* Pin:217 Name:P22_13     */
    { PORTTYPE_P               , 22, 14 }, /* Pin:218 Name:P22_14     */
    { PORTTYPE_P               , 22, 15 }, /* Pin:219 Name:P22_15     */
};


const PinIdToPortTranslation Dio_PortTypeToRH850Port[]={
    { PORTTYPE_AP,  0, 0 },
    { PORTTYPE_AP,  1, 0 },
    { PORTTYPE_JP,  0, 0 },
    { PORTTYPE_P,  0, 0 },
    { PORTTYPE_P,  1, 0 },
    { PORTTYPE_P,  2, 0 },
    { PORTTYPE_P,  3, 0 },
    { PORTTYPE_P,  8, 0 },
    { PORTTYPE_P,  9, 0 },
    { PORTTYPE_P, 10, 0 },
    { PORTTYPE_P, 11, 0 },
    { PORTTYPE_P, 12, 0 },
    { PORTTYPE_P, 13, 0 },
    { PORTTYPE_P, 18, 0 },
    { PORTTYPE_P, 19, 0 },
    { PORTTYPE_P, 20, 0 },
    { PORTTYPE_P, 21, 0 },
    { PORTTYPE_P, 22, 0 },
};

/*
 * gamma.h
 *
 *  Created on: 2 gru 2020
 *      Author: Maciej Kuźmiak
 */

#ifndef lampy_h
#define lampy_h

#include "Arduino.h"



#define EE_L1_ON_G_START  0
#define EE_L1_ON_M_START  1
#define EE_L1_ON_G_STOP   2
#define EE_L1_ON_M_STOP   4
#define EE_L1_OFF_G_START 5
#define EE_L1_OFF_M_START 6
#define EE_L1_OFF_G_STOP  7
#define EE_L1_OFF_M_STOP  8
#define EE_L1_TRYB        9
#define EE_L1_NAT_MAX    10
#define EE_L1_NAT_MAN    14

#define EE_L2_ON_G_START  18
#define EE_L2_ON_M_START  19
#define EE_L2_ON_G_STOP   20
#define EE_L2_ON_M_STOP   21
#define EE_L2_OFF_G_START 22
#define EE_L2_OFF_M_START 23
#define EE_L2_OFF_G_STOP  24
#define EE_L2_OFF_M_STOP  25
#define EE_L2_TRYB        26
#define EE_L2_NAT_MAX     27
#define EE_L2_NAT_MAN     31

#define EE_L3_ON_G_START  35
#define EE_L3_ON_M_START  36
#define EE_L3_ON_G_STOP   37
#define EE_L3_ON_M_STOP   38
#define EE_L3_OFF_G_START 39
#define EE_L3_OFF_M_START 40
#define EE_L3_OFF_G_STOP  41
#define EE_L3_OFF_M_STOP  42
#define EE_L3_TRYB        43
#define EE_L3_NAT_MAX     44
#define EE_L3_NAT_MAN     48

#define EE_L4_ON_G_START  52
#define EE_L4_ON_M_START  53
#define EE_L4_ON_G_STOP   54
#define EE_L4_ON_M_STOP   55
#define EE_L4_OFF_G_START 56
#define EE_L4_OFF_M_START 57
#define EE_L4_OFF_G_STOP  58
#define EE_L4_OFF_M_STOP  59
#define EE_L4_TRYB        60
#define EE_L4_NAT_MAX     61
#define EE_L4_NAT_MAN     65

#define EE_L5_ON_G_START  69
#define EE_L5_ON_M_START  71
#define EE_L5_ON_G_STOP   72
#define EE_L5_ON_M_STOP   73
#define EE_L5_OFF_G_START 74
#define EE_L5_OFF_M_START 75
#define EE_L5_OFF_G_STOP  76
#define EE_L5_OFF_M_STOP  77
#define EE_L5_TRYB        78
#define EE_L5_NAT_MAX     79
#define EE_L5_NAT_MAN     83

#define EE_L6_ON_G_START  87
#define EE_L6_ON_M_START  88
#define EE_L6_ON_G_STOP   89
#define EE_L6_ON_M_STOP   90
#define EE_L6_OFF_G_START 91
#define EE_L6_OFF_M_START 92
#define EE_L6_OFF_G_STOP  93
#define EE_L6_OFF_M_STOP  94
#define EE_L6_TRYB        95
#define EE_L6_NAT_MAX     96
#define EE_L6_NAT_MAN     100

#define EE_L7_ON_G_START  104
#define EE_L7_ON_M_START  105
#define EE_L7_ON_G_STOP   106
#define EE_L7_ON_M_STOP   107
#define EE_L7_OFF_G_START 108
#define EE_L7_OFF_M_START 109
#define EE_L7_OFF_G_STOP  110
#define EE_L7_OFF_M_STOP  111
#define EE_L7_TRYB        112
#define EE_L7_NAT_MAX     113
#define EE_L7_NAT_MAN     117

#define EE_RGB_RED        121
#define EE_RGB_BLUE       122
#define EE_RGB_GREEN      123


class Lampa {
  public:
    int aktywna;
    uint8_t on_g_start;   
    uint8_t on_m_start;
    uint8_t on_g_stop;
    uint8_t on_m_stop;
    uint8_t off_g_start;
    uint8_t off_m_start;
    uint8_t off_g_stop;
    uint8_t off_m_stop;
    int natezenie_max;
    int natezenie_manual;
    int natezenie;
    uint8_t tryb; 
    bool run;
    int stanPWM;
    Lampa( int pin, int PWMChannel, uint8_t EE_on_g_start, uint8_t EE_on_m_start, uint8_t EE_on_g_stop, uint8_t EE_on_m_stop, uint8_t EE_off_g_start, uint8_t EE_off_m_start, uint8_t EE_off_g_stop, uint8_t EE_off_m_stop, uint8_t EE_natezenie_max, uint8_t EE_natezenie_manual, uint8_t EE_tryb );
    //void on();
    //void off();
    int setPWM();
    int saveLampa();
    int readLampa();
    void printLampa();
    int pPWMChannel;
    int ppin;
    private:
    int _pin;
    int _PWMChannel;
    uint8_t _EE_on_g_start;   
    uint8_t _EE_on_m_start;
    uint8_t _EE_on_g_stop;
    uint8_t _EE_on_m_stop;
    uint8_t _EE_off_g_start;
    uint8_t _EE_off_m_start;
    uint8_t _EE_off_g_stop;
    uint8_t _EE_off_m_stop;
    uint8_t _EE_natezenie_max;
    uint8_t _EE_natezenie_manual;
    uint8_t _EE_tryb; 

};

void saveLampy();

// Gamma brightness lookup table <https://victornpb.github.io/gamma-table-generator>
// gamma = 2.00 steps = 1024 range = 0-1023
const uint16_t gamma_20[1024] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,
     1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,
     2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,
     4,   4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,   6,
     6,   6,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,   8,   8,   9,   9,
     9,   9,   9,  10,  10,  10,  10,  10,  11,  11,  11,  11,  11,  12,  12,  12,
    12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,  15,  15,  15,  16,  16,
    16,  16,  17,  17,  17,  17,  18,  18,  18,  18,  19,  19,  19,  19,  20,  20,
    20,  21,  21,  21,  21,  22,  22,  22,  23,  23,  23,  23,  24,  24,  24,  25,
    25,  25,  26,  26,  26,  27,  27,  27,  28,  28,  28,  29,  29,  29,  30,  30,
    30,  31,  31,  31,  32,  32,  32,  33,  33,  33,  34,  34,  35,  35,  35,  36,
    36,  36,  37,  37,  38,  38,  38,  39,  39,  39,  40,  40,  41,  41,  41,  42,
    42,  43,  43,  44,  44,  44,  45,  45,  46,  46,  46,  47,  47,  48,  48,  49,
    49,  49,  50,  50,  51,  51,  52,  52,  53,  53,  54,  54,  54,  55,  55,  56,
    56,  57,  57,  58,  58,  59,  59,  60,  60,  61,  61,  62,  62,  63,  63,  64,
    64,  65,  65,  66,  66,  67,  67,  68,  68,  69,  69,  70,  70,  71,  71,  72,
    72,  73,  73,  74,  74,  75,  76,  76,  77,  77,  78,  78,  79,  79,  80,  81,
    81,  82,  82,  83,  83,  84,  84,  85,  86,  86,  87,  87,  88,  89,  89,  90,
    90,  91,  92,  92,  93,  93,  94,  95,  95,  96,  96,  97,  98,  98,  99,  99,
   100, 101, 101, 102, 103, 103, 104, 105, 105, 106, 106, 107, 108, 108, 109, 110,
   110, 111, 112, 112, 113, 114, 114, 115, 116, 116, 117, 118, 118, 119, 120, 120,
   121, 122, 122, 123, 124, 125, 125, 126, 127, 127, 128, 129, 130, 130, 131, 132,
   132, 133, 134, 135, 135, 136, 137, 137, 138, 139, 140, 140, 141, 142, 143, 143,
   144, 145, 146, 146, 147, 148, 149, 149, 150, 151, 152, 153, 153, 154, 155, 156,
   156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167, 168, 168,
   169, 170, 171, 172, 172, 173, 174, 175, 176, 177, 177, 178, 179, 180, 181, 182,
   182, 183, 184, 185, 186, 187, 188, 188, 189, 190, 191, 192, 193, 194, 194, 195,
   196, 197, 198, 199, 200, 201, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210,
   210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 221, 222, 223, 224,
   225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
   240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
   256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271,
   273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288,
   289, 290, 291, 292, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305,
   307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 318, 319, 320, 321, 322, 323,
   324, 325, 327, 328, 329, 330, 331, 332, 333, 335, 336, 337, 338, 339, 340, 341,
   343, 344, 345, 346, 347, 348, 350, 351, 352, 353, 354, 355, 357, 358, 359, 360,
   361, 363, 364, 365, 366, 367, 369, 370, 371, 372, 373, 375, 376, 377, 378, 379,
   381, 382, 383, 384, 386, 387, 388, 389, 390, 392, 393, 394, 395, 397, 398, 399,
   400, 402, 403, 404, 405, 407, 408, 409, 410, 412, 413, 414, 416, 417, 418, 419,
   421, 422, 423, 425, 426, 427, 428, 430, 431, 432, 434, 435, 436, 437, 439, 440,
   441, 443, 444, 445, 447, 448, 449, 451, 452, 453, 455, 456, 457, 459, 460, 461,
   463, 464, 465, 467, 468, 469, 471, 472, 474, 475, 476, 478, 479, 480, 482, 483,
   484, 486, 487, 489, 490, 491, 493, 494, 496, 497, 498, 500, 501, 503, 504, 505,
   507, 508, 510, 511, 512, 514, 515, 517, 518, 519, 521, 522, 524, 525, 527, 528,
   530, 531, 532, 534, 535, 537, 538, 540, 541, 543, 544, 545, 547, 548, 550, 551,
   553, 554, 556, 557, 559, 560, 562, 563, 565, 566, 568, 569, 571, 572, 574, 575,
   577, 578, 580, 581, 583, 584, 586, 587, 589, 590, 592, 593, 595, 596, 598, 599,
   601, 602, 604, 605, 607, 609, 610, 612, 613, 615, 616, 618, 619, 621, 622, 624,
   626, 627, 629, 630, 632, 633, 635, 637, 638, 640, 641, 643, 645, 646, 648, 649,
   651, 652, 654, 656, 657, 659, 660, 662, 664, 665, 667, 669, 670, 672, 673, 675,
   677, 678, 680, 682, 683, 685, 686, 688, 690, 691, 693, 695, 696, 698, 700, 701,
   703, 705, 706, 708, 710, 711, 713, 715, 716, 718, 720, 721, 723, 725, 726, 728,
   730, 731, 733, 735, 736, 738, 740, 742, 743, 745, 747, 748, 750, 752, 754, 755,
   757, 759, 760, 762, 764, 766, 767, 769, 771, 773, 774, 776, 778, 780, 781, 783,
   785, 787, 788, 790, 792, 794, 795, 797, 799, 801, 802, 804, 806, 808, 809, 811,
   813, 815, 817, 818, 820, 822, 824, 826, 827, 829, 831, 833, 835, 836, 838, 840,
   842, 844, 845, 847, 849, 851, 853, 855, 856, 858, 860, 862, 864, 866, 867, 869,
   871, 873, 875, 877, 878, 880, 882, 884, 886, 888, 890, 892, 893, 895, 897, 899,
   901, 903, 905, 907, 908, 910, 912, 914, 916, 918, 920, 922, 924, 925, 927, 929,
   931, 933, 935, 937, 939, 941, 943, 945, 946, 948, 950, 952, 954, 956, 958, 960,
   962, 964, 966, 968, 970, 972, 974, 976, 978, 979, 981, 983, 985, 987, 989, 991,
   993, 995, 997, 999,1001,1003,1005,1007,1009,1011,1013,1015,1017,1019,1021,1023,
  };

const uint16_t gamma_22[1024] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
     1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
     2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   4,   4,
     4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,
     6,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,
     8,   8,   8,   8,   9,   9,   9,   9,   9,   9,  10,  10,  10,  10,  10,  10,
    11,  11,  11,  11,  11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  13,
    14,  14,  14,  14,  15,  15,  15,  15,  15,  16,  16,  16,  16,  17,  17,  17,
    17,  18,  18,  18,  18,  18,  19,  19,  19,  19,  20,  20,  20,  21,  21,  21,
    21,  22,  22,  22,  22,  23,  23,  23,  23,  24,  24,  24,  25,  25,  25,  25,
    26,  26,  26,  27,  27,  27,  28,  28,  28,  29,  29,  29,  29,  30,  30,  30,
    31,  31,  31,  32,  32,  32,  33,  33,  33,  34,  34,  34,  35,  35,  35,  36,
    36,  37,  37,  37,  38,  38,  38,  39,  39,  39,  40,  40,  41,  41,  41,  42,
    42,  43,  43,  43,  44,  44,  44,  45,  45,  46,  46,  46,  47,  47,  48,  48,
    49,  49,  49,  50,  50,  51,  51,  52,  52,  52,  53,  53,  54,  54,  55,  55,
    55,  56,  56,  57,  57,  58,  58,  59,  59,  60,  60,  61,  61,  61,  62,  62,
    63,  63,  64,  64,  65,  65,  66,  66,  67,  67,  68,  68,  69,  69,  70,  70,
    71,  71,  72,  72,  73,  73,  74,  75,  75,  76,  76,  77,  77,  78,  78,  79,
    79,  80,  80,  81,  82,  82,  83,  83,  84,  84,  85,  85,  86,  87,  87,  88,
    88,  89,  89,  90,  91,  91,  92,  92,  93,  94,  94,  95,  95,  96,  97,  97,
    98,  98,  99, 100, 100, 101, 102, 102, 103, 103, 104, 105, 105, 106, 107, 107,
   108, 109, 109, 110, 110, 111, 112, 112, 113, 114, 114, 115, 116, 116, 117, 118,
   118, 119, 120, 121, 121, 122, 123, 123, 124, 125, 125, 126, 127, 127, 128, 129,
   130, 130, 131, 132, 132, 133, 134, 135, 135, 136, 137, 138, 138, 139, 140, 141,
   141, 142, 143, 144, 144, 145, 146, 147, 147, 148, 149, 150, 150, 151, 152, 153,
   154, 154, 155, 156, 157, 157, 158, 159, 160, 161, 161, 162, 163, 164, 165, 166,
   166, 167, 168, 169, 170, 170, 171, 172, 173, 174, 175, 175, 176, 177, 178, 179,
   180, 181, 181, 182, 183, 184, 185, 186, 187, 187, 188, 189, 190, 191, 192, 193,
   194, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 203, 204, 205, 206, 207,
   208, 209, 210, 211, 212, 213, 214, 215, 216, 216, 217, 218, 219, 220, 221, 222,
   223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238,
   239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
   255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 269, 270, 271,
   272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 283, 284, 285, 286, 287, 288,
   289, 290, 291, 292, 294, 295, 296, 297, 298, 299, 300, 301, 303, 304, 305, 306,
   307, 308, 309, 311, 312, 313, 314, 315, 316, 317, 319, 320, 321, 322, 323, 324,
   326, 327, 328, 329, 330, 332, 333, 334, 335, 336, 338, 339, 340, 341, 342, 344,
   345, 346, 347, 348, 350, 351, 352, 353, 355, 356, 357, 358, 360, 361, 362, 363,
   365, 366, 367, 368, 370, 371, 372, 373, 375, 376, 377, 378, 380, 381, 382, 384,
   385, 386, 387, 389, 390, 391, 393, 394, 395, 397, 398, 399, 401, 402, 403, 405,
   406, 407, 409, 410, 411, 413, 414, 415, 417, 418, 419, 421, 422, 423, 425, 426,
   427, 429, 430, 432, 433, 434, 436, 437, 438, 440, 441, 443, 444, 445, 447, 448,
   450, 451, 452, 454, 455, 457, 458, 459, 461, 462, 464, 465, 467, 468, 469, 471,
   472, 474, 475, 477, 478, 480, 481, 483, 484, 485, 487, 488, 490, 491, 493, 494,
   496, 497, 499, 500, 502, 503, 505, 506, 508, 509, 511, 512, 514, 515, 517, 518,
   520, 521, 523, 524, 526, 527, 529, 530, 532, 534, 535, 537, 538, 540, 541, 543,
   544, 546, 548, 549, 551, 552, 554, 555, 557, 559, 560, 562, 563, 565, 567, 568,
   570, 571, 573, 575, 576, 578, 579, 581, 583, 584, 586, 587, 589, 591, 592, 594,
   596, 597, 599, 601, 602, 604, 605, 607, 609, 610, 612, 614, 615, 617, 619, 620,
   622, 624, 625, 627, 629, 631, 632, 634, 636, 637, 639, 641, 642, 644, 646, 648,
   649, 651, 653, 654, 656, 658, 660, 661, 663, 665, 667, 668, 670, 672, 674, 675,
   677, 679, 681, 682, 684, 686, 688, 689, 691, 693, 695, 697, 698, 700, 702, 704,
   705, 707, 709, 711, 713, 714, 716, 718, 720, 722, 724, 725, 727, 729, 731, 733,
   735, 736, 738, 740, 742, 744, 746, 747, 749, 751, 753, 755, 757, 759, 760, 762,
   764, 766, 768, 770, 772, 774, 776, 777, 779, 781, 783, 785, 787, 789, 791, 793,
   795, 796, 798, 800, 802, 804, 806, 808, 810, 812, 814, 816, 818, 820, 822, 824,
   826, 828, 829, 831, 833, 835, 837, 839, 841, 843, 845, 847, 849, 851, 853, 855,
   857, 859, 861, 863, 865, 867, 869, 871, 873, 875, 877, 879, 881, 883, 885, 887,
   889, 892, 894, 896, 898, 900, 902, 904, 906, 908, 910, 912, 914, 916, 918, 920,
   922, 925, 927, 929, 931, 933, 935, 937, 939, 941, 943, 945, 948, 950, 952, 954,
   956, 958, 960, 962, 965, 967, 969, 971, 973, 975, 977, 980, 982, 984, 986, 988,
   990, 992, 995, 997, 999,1001,1003,1005,1008,1010,1012,1014,1016,1019,1021,1023,
  };

const uint16_t gamma_24[1024] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,
     1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
     1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
     2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
     3,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,   5,
     5,   5,   5,   5,   6,   6,   6,   6,   6,   6,   6,   6,   6,   7,   7,   7,
     7,   7,   7,   7,   8,   8,   8,   8,   8,   8,   8,   8,   9,   9,   9,   9,
     9,   9,  10,  10,  10,  10,  10,  10,  11,  11,  11,  11,  11,  11,  12,  12,
    12,  12,  12,  12,  13,  13,  13,  13,  13,  14,  14,  14,  14,  14,  15,  15,
    15,  15,  15,  16,  16,  16,  16,  16,  17,  17,  17,  17,  18,  18,  18,  18,
    18,  19,  19,  19,  19,  20,  20,  20,  20,  21,  21,  21,  21,  22,  22,  22,
    22,  23,  23,  23,  23,  24,  24,  24,  24,  25,  25,  25,  26,  26,  26,  26,
    27,  27,  27,  28,  28,  28,  28,  29,  29,  29,  30,  30,  30,  31,  31,  31,
    32,  32,  32,  32,  33,  33,  33,  34,  34,  34,  35,  35,  35,  36,  36,  36,
    37,  37,  38,  38,  38,  39,  39,  39,  40,  40,  40,  41,  41,  41,  42,  42,
    43,  43,  43,  44,  44,  44,  45,  45,  46,  46,  46,  47,  47,  48,  48,  48,
    49,  49,  50,  50,  50,  51,  51,  52,  52,  53,  53,  53,  54,  54,  55,  55,
    56,  56,  56,  57,  57,  58,  58,  59,  59,  60,  60,  61,  61,  61,  62,  62,
    63,  63,  64,  64,  65,  65,  66,  66,  67,  67,  68,  68,  69,  69,  70,  70,
    71,  71,  72,  72,  73,  73,  74,  74,  75,  75,  76,  76,  77,  77,  78,  79,
    79,  80,  80,  81,  81,  82,  82,  83,  83,  84,  85,  85,  86,  86,  87,  87,
    88,  89,  89,  90,  90,  91,  91,  92,  93,  93,  94,  94,  95,  96,  96,  97,
    97,  98,  99,  99, 100, 100, 101, 102, 102, 103, 104, 104, 105, 106, 106, 107,
   107, 108, 109, 109, 110, 111, 111, 112, 113, 113, 114, 115, 115, 116, 117, 117,
   118, 119, 119, 120, 121, 121, 122, 123, 124, 124, 125, 126, 126, 127, 128, 129,
   129, 130, 131, 131, 132, 133, 134, 134, 135, 136, 137, 137, 138, 139, 140, 140,
   141, 142, 143, 143, 144, 145, 146, 146, 147, 148, 149, 149, 150, 151, 152, 153,
   153, 154, 155, 156, 157, 157, 158, 159, 160, 161, 161, 162, 163, 164, 165, 166,
   166, 167, 168, 169, 170, 171, 171, 172, 173, 174, 175, 176, 177, 177, 178, 179,
   180, 181, 182, 183, 184, 184, 185, 186, 187, 188, 189, 190, 191, 192, 192, 193,
   194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 204, 205, 206, 207, 208,
   209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
   225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
   241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 255, 256, 257,
   258, 259, 260, 261, 262, 263, 264, 265, 266, 268, 269, 270, 271, 272, 273, 274,
   275, 276, 277, 279, 280, 281, 282, 283, 284, 285, 287, 288, 289, 290, 291, 292,
   293, 295, 296, 297, 298, 299, 300, 302, 303, 304, 305, 306, 308, 309, 310, 311,
   312, 314, 315, 316, 317, 318, 320, 321, 322, 323, 324, 326, 327, 328, 329, 331,
   332, 333, 334, 336, 337, 338, 339, 341, 342, 343, 344, 346, 347, 348, 350, 351,
   352, 353, 355, 356, 357, 359, 360, 361, 363, 364, 365, 367, 368, 369, 370, 372,
   373, 374, 376, 377, 378, 380, 381, 383, 384, 385, 387, 388, 389, 391, 392, 393,
   395, 396, 398, 399, 400, 402, 403, 405, 406, 407, 409, 410, 412, 413, 414, 416,
   417, 419, 420, 421, 423, 424, 426, 427, 429, 430, 432, 433, 434, 436, 437, 439,
   440, 442, 443, 445, 446, 448, 449, 451, 452, 454, 455, 457, 458, 460, 461, 463,
   464, 466, 467, 469, 470, 472, 473, 475, 476, 478, 479, 481, 483, 484, 486, 487,
   489, 490, 492, 493, 495, 497, 498, 500, 501, 503, 505, 506, 508, 509, 511, 512,
   514, 516, 517, 519, 521, 522, 524, 525, 527, 529, 530, 532, 534, 535, 537, 539,
   540, 542, 543, 545, 547, 548, 550, 552, 553, 555, 557, 559, 560, 562, 564, 565,
   567, 569, 570, 572, 574, 576, 577, 579, 581, 582, 584, 586, 588, 589, 591, 593,
   595, 596, 598, 600, 602, 603, 605, 607, 609, 610, 612, 614, 616, 618, 619, 621,
   623, 625, 627, 628, 630, 632, 634, 636, 637, 639, 641, 643, 645, 647, 648, 650,
   652, 654, 656, 658, 660, 661, 663, 665, 667, 669, 671, 673, 674, 676, 678, 680,
   682, 684, 686, 688, 690, 692, 693, 695, 697, 699, 701, 703, 705, 707, 709, 711,
   713, 715, 717, 719, 721, 723, 724, 726, 728, 730, 732, 734, 736, 738, 740, 742,
   744, 746, 748, 750, 752, 754, 756, 758, 760, 762, 764, 766, 768, 770, 772, 774,
   777, 779, 781, 783, 785, 787, 789, 791, 793, 795, 797, 799, 801, 803, 805, 808,
   810, 812, 814, 816, 818, 820, 822, 824, 826, 829, 831, 833, 835, 837, 839, 841,
   844, 846, 848, 850, 852, 854, 856, 859, 861, 863, 865, 867, 870, 872, 874, 876,
   878, 880, 883, 885, 887, 889, 891, 894, 896, 898, 900, 903, 905, 907, 909, 912,
   914, 916, 918, 921, 923, 925, 927, 930, 932, 934, 936, 939, 941, 943, 946, 948,
   950, 952, 955, 957, 959, 962, 964, 966, 969, 971, 973, 976, 978, 980, 983, 985,
   987, 990, 992, 994, 997, 999,1002,1004,1006,1009,1011,1013,1016,1018,1021,1023,
  };


#endif /* lampy_h */
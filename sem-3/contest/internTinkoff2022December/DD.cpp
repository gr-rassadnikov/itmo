#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> d= {
        0.000000,
        0.000000,
        0.433013,
        0.500000,
        0.769421,
        1.299038,
        1.582786,
        2.060660,
        2.776250,
        3.553212,
        4.479816,
        5.598076,
        6.637360,
        7.937773,
        9.280177,
        10.841042,
        12.590925,
        14.510573,
        16.334143,
        18.418712,
        20.559340,
        22.936303,
        25.453524,
        28.179090,
        30.911100,
        33.888870,
        36.934651,
        40.211502,
        43.611084,
        47.224791,
        50.794614,
        54.603302,
        58.515475,
        62.670125,
        66.868773,
        71.318113,
        75.866112,
        80.640330,
        85.504806,
        90.588436,
        95.790259,
        101.203169,
        106.577317,
        112.174899,
        117.903228,
        123.855506,
        129.870436,
        136.098212,
        142.467646,
        149.043034,
        155.735444,
        162.638107,
        169.663063,
        176.893523,
        184.140141,
        191.598325,
        199.198330,
        207.009798,
        214.897869,
        222.990869,
        231.222015,
        239.654666,
        248.221021,
        256.984547,
        265.877283,
        274.969623,
        284.063149,
        293.361113,
        302.807794,
        312.458561,
        322.197789,
        332.136743,
        342.219724,
        352.502941,
        362.913306,
        373.518001,
        384.261775,
        395.201097,
        406.209879,
        417.416325,
        428.774198,
        440.329425,
        451.980985,
        463.826869,
        475.820640,
        488.008969,
        500.322551,
        512.826639,
        525.474904,
        538.314370,
        551.168478,
        564.216715,
        577.419568,
        590.816191,
        604.316899,
        618.009070,
        631.852926,
        645.888267,
        660.049961,
        674.400136,
        688.898970,
        703.586637,
        718.369145,
        733.341455,
        748.469140,
        763.786344,
        779.212498,
        794.826424,
        810.593407,
        826.548142,
        842.629623,
        858.896604,
        875.314251,
        891.917614,
        908.569128,
        925.408011,
        942.403752,
        959.586585,
        976.883367,
        994.365831,
        1012.003187,
        1029.830324,
        1047.777515,
        1065.912706,
        1084.200775,
        1102.672763,
        1121.253919,
        1140.019526,
        1158.942218,
        1178.049137,
        1197.273342,
        1216.680647,
        1236.243421,
        1255.989218,
        1275.864350,
        1295.921091,
        1316.131648,
        1336.523871,
        1356.962624,
        1377.584419,
        1398.364435,
        1419.327269,
        1440.411197,
        1461.676985,
        1483.101632,
        1504.710571,
        1526.439451,
        1548.355574,
        1570.427040,
        1592.679078,
        1615.049701,
        1637.601214,
        1660.310926,
        1683.201345,
        1706.215229,
        1729.409025,
        1752.759818,
        1776.290429,
        1799.953185,
        1823.794788,
        1847.792164,
        1871.968377,
        1896.228256,
        1920.667691,
        1945.265781,
        1970.043258,
        1994.946753,
        2020.029069,
        2045.272356,
        2070.694839,
        2096.239057,
        2121.968750,
        2147.854964,
        2173.918931,
        2200.107735,
        2226.474505,
        2252.999873,
        2279.703064,
        2306.534096,
        2333.542368,
        2360.708325,
        2388.051438,
        2415.528953,
        2443.182925,
        2470.993654,
        2498.980810,
        2527.028402,
        2555.253303,
        2583.637463,
        2612.198789,
        2640.890569,
        2669.759572,
        2698.789330,
        2727.996093,
        2757.329018,
        2786.841999,
        2816.514513,
        2846.362911,
        2876.341043,
        2906.495201,
        2936.808494,
        2967.297690,
        2997.918432,
        3028.714624,
        3059.669217,
        3090.799178,
        3122.065803,
        3153.507262,
        3185.106379,
        3216.880287,
        3248.756318,
        3280.807533,
        3313.018057,
        3345.403652,
        3377.922992,
        3410.617449,
        3443.472397,
        3476.502297,
        3509.661683,
        3542.996802,
        3576.493122,
        3610.163513,
        3643.967071,
        3677.944805,
        3712.081746,
        3746.392765,
        3780.838001,
        3815.456959,
        3850.234535,
        3885.185765,
        3920.275326,
        3955.538126,
        3990.958950,
        4026.552970,
        4062.228523,
        4098.077809,
        4134.086659,
        4170.269145,
        4206.588212,
        4243.080946,
        4279.734193,
        4316.560971,
        4353.520169,
        4390.652279,
        4427.946655,
        4465.413932,
        4503.017294,
        4540.793546,
        4578.729246,
        4616.837751,
        4655.082864,
        4693.500490,
        4732.077073,
        4770.826106,
        4809.715120,
        4848.776248,
        4887.995838,
        4927.387499,
        4966.892490,
        5006.569799,
        5046.406637,
        5086.415715,
        5126.563452,
        5166.883455,
        5207.363773,
        5248.016250,
        5288.803367,
        5329.762133,
        5370.881565,
        5412.173756,
        5453.604193,
        5495.206259,
        5536.967760,
        5578.900820,
        5620.972294,
        5663.215087,
        5705.616907,
        5748.189991,
        5790.904311,
        5833.789624,
        5876.833550,
        5920.048431,
        5963.347413,
        6006.817786,
        6050.447895,
        6094.249323,
        6138.191370,
        6182.304755,
        6226.578526,
        6271.023543,
        6315.605306,
        6360.357884,
        6405.270203,
        6450.355211,
        6495.580470,
        6540.976518,
        6586.532196,
        6632.258599,
        6678.125159,
        6724.162242,
        6770.358599,
        6816.725429,
        6863.234801,
        6909.914415,
        6956.752949,
        7003.761686,
        7050.891338,
        7098.191362,
        7145.651050,
        7193.281049,
        7241.053082,
        7288.995444,
        7337.098027,
        7385.370861,
        7433.782015,
        7482.363056,
        7531.103127,
        7580.015179,
        7629.069108,
        7678.292951,
        7727.676409,
        7777.229457,
        7826.924087,
        7876.788355,
        7926.811900,
        7977.005039,
        8027.341678,
        8077.847718,
        8128.512731,
        8179.347110,
        8230.286318,
        8281.395149,
        8332.663704,
        8384.101830,
        8435.683319,
        8487.434393,
        8539.345667,
        8591.426460,
        8643.647053,
        8696.036848,
        8748.585814,
        8801.305103,
        8854.168305,
        8907.201068,
        8960.392995,
        9013.753865,
        9067.257698,
        9120.930513,
        9174.762705,
        9228.763839,
        9282.909431,
        9337.223799,
        9391.697278,
        9446.339502,
        9501.108022,
        9556.045408,
        9611.142456,
        9666.408326,
        9721.818597,
        9777.397702,
        9833.136886,
        9889.044847,
        9945.093796,
        10001.311248,
        10057.687881,
        10114.233396,
        10170.924598,
        10227.784514,
        10284.803358,
        10341.990484,
        10399.321663,
        10456.821156,
        10514.480010,
        10572.307144,
        10630.279495,
        10688.419982,
        10746.719600,
        10805.187324,
        10863.750367,
        10922.481797,
        10981.373012,
        11040.432572,
        11099.637616,
        11159.011015,
        11218.544560,
        11278.246408,
        11338.090462,
        11398.102576,
        11458.274043,
        11518.613541,
        11579.100233,
        11639.754808,
        11700.568512,
        11761.550074,
        11822.676800,
        11883.971411,
        11945.425525,
        12007.047492,
        12068.815518,
        12130.751269,
        12192.846316,
        12255.109060,
        12317.502227,
        12380.063183,
        12442.783856,
        12505.672281,
        12568.706971,
        12631.909421,
        12695.271911,
        12758.802116,
        12822.475440,
        12886.316268,
        12950.316430,
        13014.484070,
        13078.799375,
        13143.282029,
        13207.923820,
        13272.732937,
        13337.688037,
        13402.810485,
        13468.092404,
        13533.541643,
        13599.137548,
        13664.900662,
        13730.823062,
        13796.912646,
        13863.119626,
        13929.493938,
        13996.027980,
        14062.729322,
        14129.577694,
        14196.593373,
        14263.769067,
        14331.112029,
        14398.598996,
        14466.253041,
        14534.066472,
        14602.046956,
        14670.175614,
        14738.471210,
        14806.926016,
        14875.547741,
        14944.316239,
        15013.251674,
        15082.346614,
        15151.608465,
        15221.017599,
        15290.593545,
        15360.328830,
        15430.230903,
        15500.266543,
        15570.469044,
        15640.831219,
        15711.360224,
        15782.036879,
        15852.880371,
        15923.883795,
        15995.054022,
        16066.368989,
        16137.850590,
        16209.491558,
        16281.299138,
        16353.255300,
        16425.377973,
        16497.659856,
        16570.108230,
        16642.704024,
        16715.466326,
        16788.388104,
        16861.476366,
        16934.712416,
        17008.114863,
        17081.676636,
        17155.404786,
        17229.241408,
        17303.244583,
        17377.407495,
        17451.736931,
        17526.214683,
        17600.858965,
        17675.663214,
        17750.633961,
        17825.750222,
        17901.032826,
        17976.474887,
        18052.083269,
        18127.840722,
        18203.764407,
        18279.847403,
        18356.096612,
        18432.493923,
        18509.057461,
        18585.780549,
        18662.669840,
        18739.707482,
        18816.911248,
        18894.274428,
        18971.803711,
        19049.469132,
        19127.300715,
};

int main(){
    int n;
    cin >> n;
    cout << fixed << setprecision(6);
    cout << d[n-1];

}
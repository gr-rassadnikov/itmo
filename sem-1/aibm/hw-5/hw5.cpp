#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <omp.h>


using namespace std;
#define uchar unsigned char

ifstream input;
ofstream output;
vector<int> picture;
double k;
int num_threads;
int width;
int height;
string p_5_6;
string check_255;
int counter_colors_r[256];
int counter_colors_g[256];
int counter_colors_b[256];

void open_files(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "please write count threads, input and output file name, parameter\n";
        exit(0);
    }

    input.open(argv[2]);
    output.open(argv[3]);
    if (!input) {
        cout << "failed to find input file\n";
        exit(0);
    }

    if (!output) {
        cout << "failed to find output file\n";
        exit(0);
    }

    string _num_threads = argv[1];
    for (auto i:_num_threads) {
        if (i<'0' || i>'9') {
            cout << "number of threads must be int\n";
            exit(0);
        }
    }
    num_threads = stoi(_num_threads);
    string _k = argv[4];
    for (auto i:_k) {
        if ((i<'0' || i>'9')&& i!='.') {
            cout << "coefficient must be number(int,float,double...)\n";
            exit(0);
        }
    }
    k = stod(_k);
    if (k>=0.5|| k<0){
        cout << "coefficient must be in [0,0.5)\n";
        exit(0);
    }

}
void read_in() {
    char e;
    p_5_6 = "";
    input.get(e);
    while (e != '\n') {
        p_5_6 = p_5_6 + e;
        input.get(e);
    }
    input.get(e);
    string _width = "";
    string _height = "";
    while (e != ' ' && e != '\n') {
        _width = _width + to_string((uchar) e - 48);
        input.get(e);
    }
    input.get(e);
    while (e != '\n') {
        _height = _height + to_string((uchar) e - 48);
        input.get(e);
    }
    input.get(e);
    check_255 = "";
    while (e != '\n') {
        check_255 = check_255 + e;
        input.get(e);

    }

    width = atoi(_width.c_str());
    height = atoi(_height.c_str());

}
void check_ppm(string p_5_6, string check_255) {
    if (p_5_6 != "P6" && p_5_6 != "P5") {
        cout << "expected P6 in file header";
        exit(0);
    }

    if (check_255 != "255") {
        cout << "expected 255 in file header after size";
    }
}
void read_picture() {
    char e;
    while (input.get(e)) {
        picture.push_back((uchar) e);
    }
}



void make_new_gray_picture(){
    int picture_size = picture.size();
    int counter_colors[256];
    int propusk = k * picture_size;
    int _propusk = propusk;
    int color_start = 0;
    int color_end = 255;

#if defined(_OPENMP)
    if (num_threads > 0) {
        omp_set_num_threads(num_threads);
    }
#endif
    int i;

#pragma omp parallel for shared(counter_colors) schedule(guided)
    for (i = 0; i < 256; i++) {
        counter_colors[i] = 0;
    }

#pragma omp parallel for shared(counter_colors, picture) schedule(guided)
    for (i = 0; i < picture_size; i++) {
        counter_colors[picture[i]]++;
    }


    for ( i = 0; i < 256; i++) {
        _propusk -= counter_colors[i];
        if (_propusk < 0) {
            color_start = i;
            break;
        }
    }


    _propusk = propusk;

    for (i = 255; i >= 0; i--) {
        _propusk -= counter_colors[i];
        if (_propusk < 0) {
            color_end = i;
            break;
        }
    }

    if (color_start > color_end) {
        color_start = (color_start + color_end) / 2;
        color_end = color_start;
    }
    int convert[256];
    int color;
    double deletel = 255.0/(color_end - color_start+1);

#pragma omp parallel for shared(convert, color_end, color_start) schedule(guided)
    for (i = 0; i < 256; i++) {
        color = (i - color_start) * deletel;
        if (color > 255) {
            color = 255;
        }
        if (color < 0) {
            color = 0;
        }
        convert[i] = color;
    }
    int cop;

#pragma omp parallel for shared(convert, picture) schedule(guided)
    for ( i = 0; i < picture_size; i++) {
        cop = picture[i];
        picture[i] = convert[cop];
    }


}
void make_new_color_picture() {
    int picture_size = picture.size();
    int propusk = k * picture_size / 3;
    int _propusk_r = propusk;
    int _propusk_g = propusk;
    int _propusk_b = propusk;
    int color_start = 0;
    int color_end = 255;
    int color_start_r = 0;
    int color_end_r = 255;
    int color_start_g = 0;
    int color_end_g = 255;
    int color_start_b = 0;
    int color_end_b = 255;

#if defined(_OPENMP)
    if (num_threads > 0) {
        omp_set_num_threads(num_threads);
    }
#endif

#pragma omp parallel sections
    {

#pragma omp section
        {
#pragma omp parallel for shared(counter_colors_r, picture) schedule(guided)
            for (int i = 0; i < picture_size; i = i + 3) {
                counter_colors_r[picture[i]]++;
            }
        }

#pragma omp section
        {
#pragma omp parallel for shared(counter_colors_g, picture) schedule(guided)
            for (int i = 1; i < picture_size; i = i + 3) {
                counter_colors_g[picture[i]]++;
            }
        }
#pragma omp section
        {
#pragma omp parallel for shared(counter_colors_b, picture) schedule(guided)
            for (int i = 2; i < picture_size; i = i + 3) {
                counter_colors_b[picture[i]]++;
            }
        }
    }

#pragma omp parallel sections
    {
#pragma omp section
        {
            for (int i = 0; i < 256; i++) {
                _propusk_r -= counter_colors_r[i];
                if (_propusk_r < 0) {
                    color_start_r = i;
                    break;
                }
            }
        }
#pragma omp section
        {
            for (int i = 0; i < 256; i++) {
                _propusk_g -= counter_colors_g[i];
                if (_propusk_g < 0) {
                    color_start_g = i;
                    break;
                }
            }
        }
#pragma omp section
        {

            for (int i = 0; i < 256; i++) {
                _propusk_b -= counter_colors_b[i];
                if (_propusk_b < 0) {
                    color_start_b = i;
                    break;
                }
            }
        }
    }



    _propusk_r = propusk;
    _propusk_g = propusk;
    _propusk_b = propusk;

#pragma omp parallel sections
    {
#pragma omp section
        {
            for (int i = 255; i >= 0; i--) {
                _propusk_r -= counter_colors_r[i];
                if (_propusk_r < 0) {
                    color_end_r = i;
                    break;
                }
            }
        }
#pragma omp section
        {
            for (int i = 255; i >= 0; i--) {
                _propusk_g -= counter_colors_g[i];
                if (_propusk_g < 0) {
                    color_end_g = i;
                    break;
                }
            }
        }
#pragma omp section
        {
            for (int i = 255; i >= 0; i--) {
                _propusk_b -= counter_colors_b[i];
                if (_propusk_b < 0) {
                    color_end_b = i;
                    break;
                }

            }
        }
    }

    color_start = min(color_start_r,min(color_start_g,color_start_b));
    color_end = max(color_end_r,max(color_end_g,color_end_b));

    if (color_start > color_end) {
        color_start = (color_start + color_end) / 2;
        color_end = color_start;
    }
    int convert[256];
    int color;
    double deletel = 255.0/(color_end - color_start+1);

#pragma omp parallel for shared(convert, color_end, color_start) private(color)  schedule(guided)
    for (int i = 0; i < 256; i++) {
        color = (i - color_start)*deletel;
        if (color > 255) {
            color = 255;
        }
        if (color < 0) {
            color = 0;
        }
        convert[i] = color;
    }
    int cop;

#pragma omp parallel for shared(convert, picture) private(cop) schedule(guided)
    for (int i = 0; i < picture_size; i++) {
        cop = picture[i];
        picture[i] = convert[cop];
    }


}

void write() {
    output << p_5_6 << '\n';
    output << width << " " << height << '\n';
    output << 255 << '\n';

    for (auto i: picture) {
        output << (uchar) i;
    }
}

int main(int argc, char *argv[]) {
    open_files(argc, argv);
    read_in();
    check_ppm(p_5_6, check_255);
    read_picture();

#if defined(_OPENMP)
    double start_t = omp_get_wtime();
#else
    time_t start_t = clock();
#endif

    if (p_5_6=="P6") {
        make_new_color_picture();
    }else if (p_5_6=="P5"){
        make_new_gray_picture();
    }

#if defined(_OPENMP)
    double end_t = omp_get_wtime();
     double t = end_t - start_t;
    printf("Time (%i thread(s)): %g ms\n", num_threads, (double) (t * 1000));
#else
    time_t end_t = clock();
    time_t t = end_t - start_t;
    printf("Time without openmp: %g ms\n", (double) (t * 1000)/CLOCKS_PER_SEC);
#endif

    write();
    input.close();
    output.close();
    return 0;

}
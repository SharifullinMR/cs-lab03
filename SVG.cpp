#include "SVG.H"
void show_histogram_text(const vector<size_t> &bins){
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1 ;
    size_t max_bin = bins[0];
    for (size_t bin : bins){
        if (bin>max_bin){
            max_bin=bin;
        }
    }
    for (size_t bin: bins)
    {
        double height = bin;
        if (max_bin > MAX_ASTERISK){
            height = MAX_ASTERISK * (static_cast<double>(bin)/max_bin);
        }
        if (bin < 100){
            cout<<" ";
        }
        if (bin < 10){
            cout<<" ";
        }
        cout<<bin<<"|";
        for (size_t i = 0; i<height; i++){
            cout<<"*";
        }
        cout<<endl;
    }
}
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end(){
    cout << "</svg>\n";
}
void svg_text(double left, double baseline, string text){
    cout<<"<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke, string fill){
    cout<<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<< "' />";
}
string
make_info_text(char M) {
    stringstream buffer;
    if (M==1){
        const auto VR = GetVersion();
        printf("Windows version %u.\n",VR);
        printf("Windows version %x.\n",VR);
        DWORD info = VR;
        DWORD mask = 0x0000ffff;
        DWORD version = info & mask;
        DWORD platform = info >> 16;
        printf("Windows version %u.\n",version);
        printf("Platform %u.\n",platform);
        DWORD mask_2 =  0b0000'0000'1111'1111;
        DWORD info_2 = VR;
        DWORD version_major = info_2 & mask_2;
        DWORD version_minor = version >> 8;
        printf("Version major %u.\n",version_major);
        printf("Version minor %u.\n",version_minor);
        if ((info & 0x40000000) == 0) {
                DWORD build = platform;
                printf("build %u.\n",build);
                buffer<<"Windows v " <<version_major<<"."<<version_minor<<" (build "<<build<<")"<<endl;
                return buffer.str();
        }
    }
    if(M==2){
        TCHAR name_pc[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD out = MAX_COMPUTERNAME_LENGTH + 1;
        GetComputerNameA(name_pc,& out );
        buffer<<" | Computer PC name: " << name_pc<<endl;
        return buffer.str();
    }
}

void show_histogram_svg(const vector<size_t>& bins) {
    {
        const auto IMAGE_WIDTH = 1000;
        const auto IMAGE_HEIGHT = 1000;
        const auto TEXT_LEFT = 20;
        const auto TEXT_BASELINE = 20;
        const auto TEXT_WIDTH = 50;
        const auto BIN_HEIGHT = 30;
        const auto BLOCK_WIDTH = 10;
        svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        double top = 0;
        double MAX = (IMAGE_WIDTH - TEXT_WIDTH)/BLOCK_WIDTH;
        size_t max_bin = bins[0];
        for (size_t bin : bins){
            if (bin>max_bin){
                max_bin=bin;
            }
        }
        for (size_t bin: bins)
        {
            double height = bin;
            if (max_bin > MAX){
                height = MAX * (static_cast<double>(bin)/max_bin);
            }
            const double bin_width = BLOCK_WIDTH * height;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top += BIN_HEIGHT;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, make_info_text(1)); top+=BIN_HEIGHT;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, make_info_text(2));
        svg_end();
    }
}

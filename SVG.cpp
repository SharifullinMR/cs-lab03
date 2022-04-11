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
void show_histogram_svg(const vector<size_t>& bins) {
    {
        const auto IMAGE_WIDTH = 400;
        const auto IMAGE_HEIGHT = 300;
        const auto TEXT_LEFT = 20;
        const auto TEXT_BASELINE = 20;
        const auto TEXT_WIDTH = 50;
        const auto BIN_HEIGHT = 30;
        size_t BLOCK_WIDTH;
        cerr<<"Enter BLOCK_WIDTH : "; cin>>BLOCK_WIDTH;
        while(BLOCK_WIDTH<3 || BLOCK_WIDTH>30){
            cerr<<"Limit! Re Enter Block WIDTH : "; cin>>BLOCK_WIDTH;
        }
        svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        double top = 0;
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
            const double bin_width = BLOCK_WIDTH * height;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top += BIN_HEIGHT;
        }
        svg_end();
    }
}

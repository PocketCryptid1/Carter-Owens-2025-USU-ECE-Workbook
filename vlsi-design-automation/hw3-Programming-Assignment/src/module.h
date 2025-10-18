#ifndef MODULE
#define MODULE

enum modType { 
    H, 
    V, 
    LEAF 
};

class module {
    public:
        modType type;
        int id;
        double area;
        double aspect_ratio;
        double width;
        double height;

        module(int id, double area, double aspect_ratio, modType type);
\
};

#endif
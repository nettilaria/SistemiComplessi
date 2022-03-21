#ifndef LINK_H
#define LINK_H
enum class LinkType : char //underling type int : 0 per null, 1 per small, etc
{

    N, //null
    SH, //small between houses
    SS,  //small between house and sorting
    M, //medium
    B  //big
 
}; //Struttura gerarchica collegamenti
class Link
{
private:
    LinkType type_;
    static const int basic_load = 3; //carico massimo del link più piccolo
    int max_load_ = basic_load * static_cast<int>(type_);
    int load_;

public:
    Link(LinkType type, int max_load, int load);
    LinkType GetType() const;
    int GetMaxLoad() const;
    int GetLoad() const;
    void SetLoad(int newload);
};
#endif

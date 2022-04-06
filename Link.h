#ifndef LINK_H
#define LINK_H
enum class LinkType : char // underling type int : 0 per null, 1 per small, etc
{

    N,  // null
    SH, // small between houses
    SS, // small between house and sorting
    M,  // medium
    B   // big

}; // Struttura gerarchica collegamenti
class Link
{
private:
    LinkType type_ = LinkType::N;
    static const int basic_load = 3; // carico massimo del link più piccolo
    int max_load_ = basic_load * static_cast<int>(type_);
    int load_ = 0;
    int number_ = 0; // number that identifies the type of link during the print

public:
    Link(LinkType type, int load);
    Link() = default;
    LinkType GetType() const;
    void SetType(LinkType T);
    int GetMaxLoad() const;
    int GetLoad() const;
    void SetLoad(int newload);
    int GetNumber() const;
    void SetNumber(int n);
};
#endif
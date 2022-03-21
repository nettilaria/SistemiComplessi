#ifndef BUILDING_H
#define BUILDING_H
enum class BuildingType : char //underlying type int: 0 per H, 1 per S, 2 per C
{
    H, //houses
    S, //sorting
    C  //central
};     //Struttura gerarchica edifici

class Building
{
private:
    BuildingType type_ = BuildingType::H;
    double need_ = 0.0; 
    double entry_potential_ = 0.0; //settato a zero, perchè definito dalla dinamica
    bool sorting_link_ = false;

public:
    Building(BuildingType type, double need, double entry_potential);
    Building() = default; //costruttore di default insieme alle condizioni uguali nel private

    BuildingType GetType() const;
    double GetNeed() const;
    double GetEntryPotential() const;
    bool GetSortingLink() const;
    void SetEntryPotential(double entry_potential);
    void SetNeed(double need);
    void SetType(BuildingType type);
    void SetSortingLink(bool Sorting);
};
#endif

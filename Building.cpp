#include "Building.h"
Building::Building(BuildingType type, double need, double entry_potential) : type_{type}, need_{need}, entry_potential_{entry_potential}
{
}
BuildingType Building::GetType() const
{
    return type_;
};
double Building::GetNeed() const
{
    return need_;
};
bool Building::GetSortingLink() const
{
    return sorting_link_;
};
double Building::GetEntryPotential() const
{

    return entry_potential_;
};
void Building::SetEntryPotential(double entry_potential)
{
    entry_potential_ = entry_potential;
}
void Building::SetNeed(double need)
{
    need_ = need;
}
void Building::SetType(BuildingType type)
{
    type_ = type;
}
void Building::SetSortingLink(bool Sorting)
{
    sorting_link_ = Sorting;
}

//sus.eseguibile
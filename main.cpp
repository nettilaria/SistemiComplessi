#include "Building.h"
#include "Link.h"
#include <iostream>
#include <array>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <vector>
int main() //le modifiche vanno sus
{
    int const N = 40;                                //N è numero di nodi, N^2-N il numero di link possibili
    std::array<std::array<int, N>, N> adj_matrix{0}; //matrice di adiacenza, con int come pesi
    std::array<Building, N> nodes;
    std::vector<int> Centrall(0); //vettore che tiene gli indici delle centrali di array
    double Total_potential = 0.0;
    int nofSorting = 0;
    int nofCentral = 0;
    int nofHouse = 0;
    int nofBiglink = 0;
    int nofSmalllink = 0; //houses
    int nofHSLink = 0;    //house sorting
    int nofMediumlink = 0;

    std::random_device rd; //   seed
    std::default_random_engine gen(rd());
    //std::discrete_distribution<int> link_dist({4, 3, 2, 1}); // parametri tra 0 e 3, per tre link più link non esistente
    //dal link inesistente a quello che collega le centrali //Se non funziona è colpa di Tinca
    std::discrete_distribution<int> nodeType_dist({10, 3, 1});
    std::normal_distribution<double> needfluct_dist(0.0, 0.33); //distribuzione guassiana di fluttuazioni nella richiesta di energia delle case
    std::uniform_real_distribution<double> link_dist(0.0, 1.0); //distribuzione uniforme per distribuzione dei link, generato come proporzioni programma arcelli
    std::uniform_int_distribution<int> forCentralchoice(0, N - 1);
    std::uniform_int_distribution<int> forCentralBuilding(0, N - 1); //distribuzione che sceglie, in caso non si avessero centrali, la posizione in nodes di BuildingType::C

    for (int k = 0; k < N; ++k) //settaggio dei nodi
    {
        int numtype = nodeType_dist(gen); //numtype = type of node
        if (numtype == 0)
        {
            double fluct = needfluct_dist(gen);
            nodes[k].SetType(BuildingType::H);
            nodes[k].SetNeed(7.2 + fluct); //consumo medio giornaliero di una famiglia media in kW/h
            //std::cout<<"house " <<nodes[k].GetNeed()<<std::endl;
            nofHouse++;
        }
        else if (numtype == 1)
        {
            nodes[k].SetType(BuildingType::S);
            nofSorting++;

            //std::cout<<"sorting "<<nodes[k].GetNeed()<<std::endl;
        }

        else
        {
            double entrypotcentral = 100; //da aggiustare
            nodes[k].SetType(BuildingType::C);
            // std::cout<<"central "<<nodes[k].GetNeed()<<std::endl;
            nodes[k].SetEntryPotential(entrypotcentral); //da aggiustare
            Total_potential += entrypotcentral;
            nofCentral++;
            Centrall.push_back(k);
        }
    }
    if (nofCentral == 0)
    { //Controllo per non avere un numero nullo di centrali.
        int positionofC = forCentralBuilding(gen);
        nodes[positionofC].SetType(BuildingType::C);
    }

    for (int k = 0; k < nofCentral; k++)
    {
        std::cout << Centrall[k] << " ";
    }

    std::cout << "nofcentral: " << nofCentral << std::endl;
    std::cout << "nofHouse: " << nofHouse << std::endl;
    std::cout << "nofSorting: " << nofSorting << std::endl;
    int j = 0; //j è fuori per poter calcolare solo il triangolo superiore della matrice dato che è simmetrica
    int counter = 0;
    std::cout << " Il problema è nel codice scritto 80"<<std::endl;

    for (int i = 0; i < N; ++i)
    {
        std::cout << " Il problema è nel codice scritto 84"<<std::endl;
        int y = 0;
        int pi = 0;

        BuildingType node_i = nodes[i].GetType();

        //DA GENERARE MATRICE DI ADIACENZA, CONTROLLANDO LA NATURA DEI VARI NODI.
        for (j; j < N; ++j)
        {
            std::cout << " Il problema è nel codice scritto 93"<<std::endl;
            double rnd = link_dist(gen); //generazione variabile uniforme della probabilità che avvenga link
            BuildingType node_j = nodes[j].GetType();
            if (i == j)
            {
                adj_matrix[i][j] = 0;
            }
            else
            {
                std::cout << " Il problema è nel codice scritto 102"<<std::endl;
                if (node_i == BuildingType::H && node_j == BuildingType::H)
                {                    //casa-casa
                 std::cout << " Il problema è nel codice scritto 105"<<std::endl;
                    if (rnd <= 0.30) //si suppone che, su 100 case, una casa sia collegata con altre 10.
                    {
                        adj_matrix[i][j] = 1; //link small
                        nofSmalllink++;
                        y++;
                    }
                }
                else if (node_i == BuildingType::H && node_j == BuildingType::S)
                { //casa-smistamento
                 std::cout << " Il problema è nel codice scritto 115"<<std::endl;
                    //if (rnd <= (1 / nofSorting)) //si suppone che la probabilità di avere questo link sia 1/# smistamento
                    if (rnd <= 0.20)
                    {
                        adj_matrix[i][j] = 4; //Sempre 1 perchè l'energia che confluisce è sempre la medesima
                        nofHSLink++;
                    } //link small
                }
                else if ((node_i == BuildingType::H && node_j == BuildingType::C) || (node_i == BuildingType::C && node_j == BuildingType::H))
                {
                     std::cout << " Il problema è nel codice scritto 125"<<std::endl;
                    adj_matrix[i][j] = 0;
                }
                else if (node_i == BuildingType::S && node_j == BuildingType::H)
                {
                    if (rnd <= 0.20)
                    {
                        adj_matrix[i][j] = 4; //Sempre 1 perchè l'energia che confluisce è sempre la medesima
                        nofHSLink++;
                    } //li
                }
                else if (node_i == BuildingType::S && node_j == BuildingType::S)
                { //smistamento-smistamento
                    if (rnd <= 0.10)
                    {
                        adj_matrix[i][j] = 2;
                        nofMediumlink++;
                    }
                }

                else if (node_i == BuildingType::S && node_j == BuildingType::C)
                {
                    std::cout << " Il problema è nel codice scritto qui";
                    //smistamento- centrale
                    /*  int flag = j;
                    bool p = false;
                    double probCentral = 1 / (nofCentral);
                    double z = 1;
                    if (nodes[i].GetSortingLink() == false)
                    {
                        while (p == false)
                        {

                            double rn = link_dist(gen);
                            if (z <= probCentral)
                            {
                                adj_matrix[i][flag] = 3;
                                p = true;
                                nofBiglink++;
                                pi++;
                                nodes[i].SetSortingLink(true);
                            }
                            if (nodes[i].GetSortingLink() == false)
                            {
                                z = z - rn;

                                while (nodes[flag + 1].GetType() != BuildingType::C)
                                {
                                    if (flag < N)
                                    {
                                        flag++;
                                    }
                                    else
                                    {

                                        flag = 0;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }*/
                    if (nodes[i].GetSortingLink() == false)
                    {

                        int rn = forCentralchoice(gen); //variabile intera che assume valori da 1 ad N
                        for (int l = 0; l < N;)
                        {
                            if (rn == Centrall[l])
                            {
                                adj_matrix[i][j] = 3;
                                nodes[i].SetSortingLink(true);
                            }
                            else
                            {
                                l++;
                            }
                        }
                    }
                    else
                    {
                        adj_matrix[i][j] = 0;
                    }
                }
                /* std::uniform_int_distribution<int> forCentralchoice_(0,nofCentral);
                int rn = forCentralchoice_(gen);
                for (int K=0; K<N; K++) {
                            int contatore=0;
                            if(nodes[K].GetType()==BuildingType::C){
                                    conatore++;
                                   }

                            if(contatore=rn){

                             adj_matrix[i][K] = 3;

                             break;

                            }

                    

                }   */

                else if (node_i == BuildingType::C && node_j == BuildingType::S)
                {
                    if(nodes[j].GetSortingLink()==false){
                    
                    double rn = link_dist(gen);
                    if (rn <= 0.50)
                    {
                        adj_matrix[i][j] = 3;
                        nofBiglink++;
                    }
                    }
                    else{
                        

                    }
                }

                else if (node_i == BuildingType::C && node_j == BuildingType::C){
                     adj_matrix[i][j] = 0;

                }

            }
        }
        counter++;
        j = counter;
    }

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            if (adj_matrix[i][k] == 0) //null
            {
                printf("\033[33m0 ");
            }
            else if (adj_matrix[i][k] == 1) //hh
            {
                //std::cout << "       ";
                printf("\033[31m1 ");
            }
            else if (adj_matrix[i][k] == 2) // ss
            {
                //std::cout << "       ";
                printf("\033[32m2 ");
            }
            else if (adj_matrix[i][k] == 3) //cs
            {
                // std::cout << "       ";
                printf("\033[36m3 ");
            }
            else //hs
                printf("\033[37m4 ");
        }
        std::cout << std::endl;
    }
    std::cout << "nofSmalllink :" << nofSmalllink << "\n";
    std::cout << "nofHouseSortingLink: " << nofHSLink << "\n";
    std::cout << "nofMediumlink :" << nofMediumlink << "\n";
    std::cout << "nofBiglink :" << nofBiglink << "\n";
}

//Nota: Sarebbe meglio differenziare i link casa-casa, casa-smistamento. Non tanto per una questione di portata energetica, quanto per differenziarli.
//E' diverso colpire uno dei due link a livello di danni.
//Mettere controllo per avere per avere sicurezza che almeno una casa sia collegata ad uno smistamento
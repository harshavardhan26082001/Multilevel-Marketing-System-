#include <stdio.h>
#include <stdlib.h>

#define Maxspots 30

typedef struct parknode{
        char Parking_level, dedicated_wing;
        int no_of_compact_spots, no_of_large_spots, status_compactspots[Maxspots], status_large_spots[Maxspots];
        int filledcompact, filledlarge;
        struct parknode *next;
} parknode;

typedef struct vehicle{
        int vehicle_number;
        int wheels;
        char alloted_level;
        char spot_type;
        int allocated_num;
        struct vehicle *nextvehicle;
} vehicle;

typedef struct flatnode{
        int wing_id, flat_id, no_of_two_wheelers, no_of_four_wheelers;
        vehicle *vehicledetails;
        struct flatnode *nextflat;
} flatnode;

parknode *createParkinglist(parknode *Parking_Lot)
{
        int i;
        parknode *temp;
        Parking_Lot = (parknode *)malloc(sizeof(parknode));
        Parking_Lot -> Parking_level = 'A';
        Parking_Lot -> dedicated_wing = 'A';
        Parking_Lot -> no_of_compact_spots = 25;
        Parking_Lot -> no_of_large_spots = 20;
        for (i = 0; i < 25; i++)
                Parking_Lot -> status_compactspots[i] = 0;
        Parking_Lot -> filledcompact = 0;
        for (i = 0; i < 20; i++)
                Parking_Lot -> status_large_spots[i] = 0;
        Parking_Lot -> filledlarge = 0;

        temp = (parknode *)malloc(sizeof(parknode));
        temp -> Parking_level = 'B';
        temp -> dedicated_wing = 'B';
        temp -> no_of_compact_spots = 23;
        temp -> no_of_large_spots = 24;
        for (i = 0; i < 23; i++)
                temp -> status_compactspots[i] = 0;
        temp -> filledcompact = 0;
        for (i = 0; i < 24; i++)
                temp -> status_large_spots[i] = 0;
        temp -> filledlarge = 0;
        Parking_Lot -> next = temp;

        temp = (parknode *)malloc(sizeof(parknode));
        temp -> Parking_level = 'C';
        temp -> dedicated_wing = 'C';
        temp -> no_of_compact_spots = 29;
        temp -> no_of_large_spots = 27;
        for (i = 0; i < 29; i++)
                temp -> status_compactspots[i] = 0;
        temp -> filledcompact = 0;
        for (i = 0; i < 27; i++)
                temp -> status_large_spots[i] = 0;
        temp -> filledlarge = 0;
        Parking_Lot -> next -> next = temp;
        Parking_Lot -> next -> next -> next = NULL;
        return Parking_Lot;
}

void traverseParkinglist(parknode *Parking_Lot)
{
        printf("\n\nParking Lot Details :");
        int i;
        do
        {
                printf("\nParking Lot for wing : %c", Parking_Lot -> dedicated_wing);
                printf("\nParking Level : %c", Parking_Lot -> Parking_level);
                printf("\nNumber of Compact Spots = %d", Parking_Lot -> no_of_compact_spots);
                printf("\nFilled Compact Spots = %d\n", Parking_Lot -> filledcompact);
                for(i = 0 ; i < Parking_Lot -> no_of_compact_spots ; ++i)
                        printf("%d  ", Parking_Lot -> status_compactspots[i]);
                printf("\nNumber of Large Spots = %d", Parking_Lot -> no_of_large_spots);
                printf("\nFilled Large Spots = %d\n", Parking_Lot -> filledlarge);
                for(i = 0 ; i < Parking_Lot -> no_of_large_spots ; ++i)
                        printf("%d ", Parking_Lot -> status_large_spots[i]);
                Parking_Lot = Parking_Lot -> next;
        } while (Parking_Lot != NULL);
}

flatnode *pushflatnode(flatnode *Flat_Details, int wing_id, int flat_id, int no_of_two_wheelers, int no_of_four_wheelers, FILE **flatdetails)
{
        flatnode *temp = (flatnode *)malloc(sizeof(flatnode));
        temp -> wing_id = wing_id;
        temp -> flat_id = flat_id;
        temp -> no_of_two_wheelers = no_of_two_wheelers;
        temp -> no_of_four_wheelers = no_of_four_wheelers;
        int i;
        temp -> vehicledetails = NULL;
        vehicle *temp1;
        for(i = 0 ; i < no_of_two_wheelers ; ++i)
        {
                temp1 = (vehicle *)malloc(sizeof(vehicle));
                fscanf(*flatdetails, "%d", &(temp1 -> vehicle_number));
                temp1 -> wheels = 2;
                temp1 -> alloted_level = 'G';
                temp1 -> allocated_num = -1;
                temp1 -> spot_type = 'G';
                temp1 -> nextvehicle = temp -> vehicledetails;
                temp -> vehicledetails = temp1;
        }
        for(i = 0 ; i < no_of_four_wheelers ; ++i)
        {
                temp1 = (vehicle *)malloc(sizeof(vehicle));
                fscanf(*flatdetails, "%d", &(temp1 -> vehicle_number));
                temp1 -> wheels = 4;
                temp1 -> alloted_level = 'G';
                temp1 -> allocated_num = -1;
                temp1 -> spot_type = 'G';
                temp1 -> nextvehicle = temp -> vehicledetails;
                temp -> vehicledetails = temp1;
        }
        temp -> nextflat = Flat_Details;
        Flat_Details = temp;
        return Flat_Details;
}

flatnode *createFlatlist(flatnode *Flat_Details)
{
        Flat_Details = NULL;
        int i, j, k, no2w = 0, no4w = 0;
        FILE *flatdetails;
        flatdetails = fopen("flatdetails.txt", "r");
        for(k = 3 ; k > 0 ; --k)
                for(i = 9 ; i > 0 ; --i)
                        for(j = 4 ; j > 0 ; --j)
                        {
                                fscanf(flatdetails, "%d", &no2w);
                                fscanf(flatdetails, "%d", &no4w);
                                Flat_Details = pushflatnode(Flat_Details, k, (k * 100 + i * 10 + j), no2w, no4w, &flatdetails);
                        }
        fclose(flatdetails);
        return Flat_Details;
}

void traverseFlatlist(flatnode *Flat_Details)
{
        vehicle *tempvehicle;
        printf("\n\nFlat Details :");
        while (Flat_Details != NULL)
        {
                printf("\nWID = %d, FID = %d, NO4W = %d", Flat_Details -> wing_id, Flat_Details -> flat_id, Flat_Details -> no_of_four_wheelers);
                tempvehicle = Flat_Details -> vehicledetails;
                if(tempvehicle != NULL && tempvehicle -> wheels == 4)
                        printf("(");
                while(tempvehicle != NULL && tempvehicle -> wheels == 4)
                {
                        printf("%d(Level : %c, SpotType:%c, ParkNo:%d) ", tempvehicle -> vehicle_number, tempvehicle -> alloted_level, tempvehicle -> spot_type, tempvehicle -> allocated_num);
                        tempvehicle = tempvehicle -> nextvehicle;
                        if(tempvehicle == NULL || tempvehicle -> wheels != 4)
                                printf("\b)");
                }
                printf(", NO2W = %d", Flat_Details -> no_of_two_wheelers);
                if(tempvehicle != NULL)
                        printf("(");
                while(tempvehicle != NULL)
                {
                        printf("%d(Level:%c, SpotType:%c, ParkNo:%d) ", tempvehicle -> vehicle_number, tempvehicle -> alloted_level, tempvehicle -> spot_type, tempvehicle -> allocated_num);
                        tempvehicle = tempvehicle -> nextvehicle;
                        if(tempvehicle == NULL)
                                printf("\b)");
                }
                Flat_Details = Flat_Details -> nextflat;
        }
}

void Map_Flat_VehicleNo_Parkingspot(flatnode *Flat_Details, parknode *Parking_Lot)
{
        flatnode *tempflat;
        tempflat = Flat_Details;
        vehicle *tempvehicle;
        int cs[] = {0, 0, 0}, csmax[] = {25, 23, 29}, ls[] = {0, 0, 0}, lsmax[] = {20, 24, 27}, wi;
        while (tempflat != NULL)
        {
                tempvehicle = (tempflat -> vehicledetails);
                wi = (tempflat -> wing_id);
                
                if(tempvehicle != NULL && (tempvehicle -> wheels) == 4)
                {
                        if(ls[wi - 1] < lsmax[wi - 1])
                        {
                                tempvehicle -> alloted_level = wi - 1 + 'A';
                                tempvehicle -> spot_type = 'l';
                                tempvehicle -> allocated_num = ls[wi - 1];
                                ++ls[wi - 1];
                                tempvehicle = tempvehicle -> nextvehicle;
                        }
                        if(wi <= 2 && tempvehicle != NULL && (tempvehicle -> wheels) == 4 && ls[wi] < lsmax[wi])
                        {
                                tempvehicle -> alloted_level = wi + 'A';
                                tempvehicle -> spot_type = 'l';
                                tempvehicle -> allocated_num = ls[wi];
                                ++ls[wi];
                                tempvehicle = tempvehicle -> nextvehicle;
                        }
                        if(wi <= 1 && tempvehicle != NULL && (tempvehicle -> wheels) == 4 && ls[wi + 1] < lsmax[wi + 1])
                        {
                                tempvehicle -> alloted_level = wi + 1 + 'A';
                                tempvehicle -> spot_type = 'l';
                                tempvehicle -> allocated_num = ls[wi + 1];
                                ++ls[wi + 1];
                                tempvehicle = tempvehicle -> nextvehicle;
                        }
                        while (tempvehicle != NULL && (tempvehicle -> wheels) != 2)
                        {
                                tempvehicle = tempvehicle -> nextvehicle;
                        }
                }

                while (tempvehicle != NULL && cs[wi - 1] < csmax[wi - 1])
                {
                        tempvehicle -> alloted_level = wi - 1 + 'A';
                        tempvehicle -> spot_type = 'c';
                        tempvehicle -> allocated_num = cs[wi - 1];
                        ++cs[wi - 1];
                        tempvehicle = tempvehicle -> nextvehicle;
                }
                tempflat = tempflat ->nextflat;                                                    
        }
        Parking_Lot -> filledcompact = cs[0];
        Parking_Lot -> filledlarge = ls[0];
        Parking_Lot -> next -> filledcompact = cs[1];
        Parking_Lot -> next -> filledlarge = ls[1];
        Parking_Lot -> next -> next -> filledcompact = cs[2];
        Parking_Lot -> next -> next -> filledlarge = ls[2];
}

void Park_vehicle(flatnode *Flat_Details, parknode *Parking_Lot)
{
        flatnode *tempflat = Flat_Details;
        parknode *temppark;
        vehicle *tempvehicle;
        int alloted = 0;

        while (tempflat != NULL)
        {
                tempvehicle = tempflat -> vehicledetails;
                while (tempvehicle != NULL)
                {
                        if (tempvehicle -> alloted_level == 'G' && tempvehicle -> wheels == 4)
                        {
                                temppark = Parking_Lot;
                                alloted = 0;
                                while (temppark != NULL && alloted == 0)
                                {
                                        if(temppark -> no_of_large_spots > temppark -> filledlarge)
                                        {
                                                tempvehicle -> alloted_level = temppark -> Parking_level;
                                                tempvehicle -> spot_type = 'l';
                                                tempvehicle -> allocated_num = temppark -> filledlarge;
                                                ++(temppark -> filledlarge);
                                                alloted = 1;
                                        }
                                        temppark = temppark -> next;
                                }
                                temppark = Parking_Lot;
                                while (temppark != NULL && alloted == 0)
                                {
                                        if(temppark -> no_of_compact_spots > (temppark -> filledcompact + 1))
                                        {
                                                tempvehicle -> alloted_level = temppark -> Parking_level;
                                                tempvehicle -> spot_type = 'c';
                                                tempvehicle -> allocated_num = temppark -> filledcompact;
                                                ++(temppark -> filledcompact);
                                                alloted = 1;
                                        }
                                        temppark = temppark -> next;
                                }
                        }
                        tempvehicle = tempvehicle -> nextvehicle;
                }
                tempflat = tempflat -> nextflat;
        }

        tempflat = Flat_Details;
        while (tempflat != NULL)
        {
                tempvehicle = tempflat -> vehicledetails;
                while (tempvehicle != NULL)
                {
                        if (tempvehicle -> alloted_level == 'G' && tempvehicle -> wheels == 2)
                        {
                                temppark = Parking_Lot;
                                alloted = 0;
                                while (temppark != NULL && alloted == 0)
                                {
                                        if(temppark -> no_of_compact_spots > temppark -> filledcompact)
                                        {
                                                tempvehicle -> alloted_level = temppark -> Parking_level;
                                                tempvehicle -> spot_type = 'c';
                                                tempvehicle -> allocated_num = temppark -> filledcompact;
                                                ++(temppark -> filledcompact);
                                                alloted = 1;
                                        }
                                        temppark = temppark -> next;
                                }
                        }
                        tempvehicle = tempvehicle -> nextvehicle;
                }
                tempflat = tempflat -> nextflat;
        }

        tempflat = Flat_Details;
        while (tempflat != NULL)
        {
                tempvehicle = tempflat -> vehicledetails;
                while (tempvehicle != NULL)
                {
                        if(tempvehicle -> alloted_level == 'A')
                                temppark = Parking_Lot;
                        else if(tempvehicle -> alloted_level == 'B')
                                temppark = Parking_Lot -> next;
                        else if(tempvehicle -> alloted_level == 'C')
                                temppark = Parking_Lot -> next -> next;
                        else temppark = NULL;
                        if(temppark != NULL)
                        {
                                if(tempvehicle -> spot_type == 'c')
                                {
                                        if(tempvehicle -> wheels == 4)
                                                temppark -> status_compactspots[(tempvehicle -> allocated_num) + 1] = 1;
                                        temppark -> status_compactspots[tempvehicle -> allocated_num] = 1;
                                }
                                else
                                        temppark -> status_large_spots[tempvehicle -> allocated_num] = 1;
                        }
                        tempvehicle = tempvehicle -> nextvehicle;
                }
                tempflat = tempflat -> nextflat;
        }
}

int main()
{
        printf("\nParking Lot System");
        parknode *Parking_Lot;
        flatnode *Flat_Details;
        Parking_Lot = createParkinglist(Parking_Lot);
        Flat_Details = createFlatlist(Flat_Details);
        Map_Flat_VehicleNo_Parkingspot(Flat_Details, Parking_Lot);
        traverseFlatlist(Flat_Details);
        Park_vehicle(Flat_Details, Parking_Lot);
        traverseParkinglist(Parking_Lot);
        return 0;
}

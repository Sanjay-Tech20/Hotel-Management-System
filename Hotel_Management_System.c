// Hotel Management System 
#include<stdio.h>
#include <string.h>
#define HOTEL_ROOMS 50
    struct Reservation
    {
        int roomNumber;
        char guestName[100];
        int isReserved;
    };
    struct Reservation reservations[HOTEL_ROOMS];

     void Room_Booking();
     void Checking_Availability();
     void Cancel_Reservation();
     void Search();
     void Data_loading();
     void Data_saving();

    int main() {
    Data_loading();
    int choice;
    while(1){
        printf("\n--- Hotel Reservation System ---\n");
        printf("1. Booking Room\n");
        printf("2. Check Room Availability\n");
        printf("3. Cancel Reservation\n");
        printf("4. Search by name for \n");
        printf("5. Exit\n");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);

        if(choice==1){
            Room_Booking();
        }
        else if(choice==2){
            Checking_Availability();
        }
        else if(choice==3){
            Cancel_Reservation();
        }else if (choice==4)
        {
            Search();
        }
     else if(choice==5){
            printf("Existing Program...\n");
            Data_saving();
            break;
    }
    else{
        printf("Please Enter the Valid Choice.........\n");
    }
    }
    return 0;
}
 void Room_Booking(){
    int room_no;
    printf("Enter room number(1-50):");
    scanf("%d",&room_no);
    if(room_no<1 || room_no>HOTEL_ROOMS){
        printf("Invalid room number...!");
        return;
    }
    struct Reservation *ptr = &reservations[room_no-1];
    if(ptr->isReserved==1){
        printf("Sorry,room %d is already booked by %s\n",room_no,ptr->guestName);
    }
    else{
        printf("Enter guest name:");
        getchar();
        fgets(ptr->guestName,100,stdin);
        ptr->guestName[strcspn(ptr->guestName,"\n")]='\0';
        ptr->isReserved=1;
        printf("Room %d booked successfully!\n", room_no);
    }
 }
 void Checking_Availability(){
    printf("\n---Available rooms---\n");
    int found=0, row_count=0;
    int avail=0,reserved=0 ,totalrooms=0;
    for(int i=0;i<HOTEL_ROOMS;i++){
        if(reservations[i].isReserved==0){
            printf("Room %2d: Available  |  ", reservations[i].roomNumber);
            found=1;
            avail++;
        }else{
            printf("Room %2d: reserved   |  ", reservations[i].roomNumber);
            reserved++;
            }
            totalrooms++; 
            row_count++;
            if (row_count%3==0) {
                printf("\n");
            }
    }
        printf("\ntotal rooms=%d\t",totalrooms);
        printf("\nreserved rooms=%d\t",reserved);
        printf("availible rooms=%d",avail);
    if(found==0){
        printf("No Room Available....!\n");
    }
 }
 void Cancel_Reservation(){
    int rnum;
    printf("Enter room number(1-50) :: ");
    scanf("%d",&rnum);
    if(rnum<1||rnum>HOTEL_ROOMS){
        printf("Invalid room number!\n");
        return;
    }
    if(reservations[rnum-1].isReserved==0){
        printf("Room %d is already vacant.\n", rnum);
    }
    else{
        reservations[rnum-1].isReserved=0;
        strcpy(reservations[rnum-1].guestName,"N/A");
        printf("Reservation for room %d has been cancelled successfully!\n", rnum);
    }
 }

 void Data_saving(){
    FILE *fp= fopen("hotel_reservations.txt","w");
    if(fp==NULL){
        printf("File nahi khuli!Data save nahi hua.\n");
        return;
    }
    for(int i=0;i<HOTEL_ROOMS;i++){
       fprintf(fp,"Room: %d\n",reservations[i].roomNumber);
       fprintf(fp,"Name: %s\n",reservations[i].guestName);
       fprintf(fp,"Status: %d\n",reservations[i].isReserved);
       fprintf(fp,"----------\n");
    }
    fclose(fp);
    printf("All data saved....\n");
 }

 void Search() {
    char name[100];
    int found = 0;
    printf("\nEnter Guest Name to search: ");
    getchar(); 
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < HOTEL_ROOMS; i++) {
        if (reservations[i].isReserved == 1 && stricmp(reservations[i].guestName, name) == 0) {
            printf("Room %d is Booked by %s\n", reservations[i].roomNumber, reservations[i].guestName);
            found = 1;
        }
    }
    if (found==0) {
        printf("No active reservation found for guest: %s\n", name);
    }
}

 void Data_loading(){
    FILE *fp= fopen("hotel_reservations.txt","r");
    if(fp==NULL){
        for(int i=0;i<HOTEL_ROOMS;i++){
            reservations[i].roomNumber = i+1;
            strcpy(reservations[i].guestName,"N/A");
            reservations[i].isReserved=0;
        }
        return;
    }
    int j=0;
    while(fscanf(fp,"Room: %d\nName: %[^\n]\nStatus: %d\n----------\n",
        &reservations[j].roomNumber,
        reservations[j].guestName,
        &reservations[j].isReserved)!=EOF){
            j++;
        }
        fclose(fp);
 }
 
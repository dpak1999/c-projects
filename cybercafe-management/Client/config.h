
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <string.h>
#include <time.h> 
#include <winsock2.h>   
#include <process.h>    
#define DEFAULT_PORT 5000
#define STRLEN 256
#define NUM_CLIENTS 2
#define ESC 27
#define F2 60

FILE *ip;


int port_add ; //default
char ipaddress[50];
int no_of_clients = 0;  //counter for number of clients being connected
char recMessage[STRLEN];
char sendMessage[STRLEN];
char *client_ip_address;

//variables to be sent to the server

int computer_id=5;
int service_id=0;;
int log_stat=0;
bool is_member=0;   // to see if the current customer is a member or not 1 means member, 2 means admin, 0 means guest
char username[20];
char password[20];
int tot_cost=0;
char CyberName[20];
int fixed_rate;
int tot_service;
int cost_changed=0;
int check_flag = 0;
//Input and Output Handles

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE time_thread;


//for maximizing window
extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow (void);

SOCKET Socket;
struct client
{
    sockaddr_in c_address;
    int c_addr_len;
    SOCKET c_socket;
    bool connected;
    bool turn;
};
struct client c[NUM_CLIENTS]; //struct client c[n]; if multiple clients

struct service {
  char name[15];
  int rate;
}items[10];

struct ip_info
{
    char ip_address[50];
    int port_no;
    int client_no;
};
struct ip_info ip1;


COORD coord = {0, 0}; // sets coordinates to 0,0
COORD max_buffer_size = GetLargestConsoleWindowSize(hOut);
COORD max_res,cursor_size;



bool SOCKET_START = false;  //TRUE if socket is already initialised
bool login_server = false;  // TRUE if server is alerady logged in
bool done = false;  //if it is true, the communication ends


time_t t;  // structure for accessing system time


//Global variables
int i,j,k;

int flag_menu=0; //flag for menu
int to_tray = 0; //to check if the user wants to go back to tray mode
//Interface Function declarations
void main_menu();  //Main interface of the system


//Utility functions
void gotoxy(int x,int y); //jump to coordinates
void delay(unsigned int mseconds); //create a delay
void console_resize(int console_id);
void reset_console();
void login_screen();
void admin_page();
void show_menu();
void service_menu();
void settings_menu();
void order(int ord);
void chg_compID();
void chg_password();
void credits();
void log_out();
void help_window();
void console_settings();
void reset_variables();


//Server client related functions
void start_socket();
void connect_server();
void cl_send_data(char* menu_selected, char* log_status);
int cl_recv_data();
int get_code();
//thread functions
void show_time(void *param);
void update_price(void *param);


void readMessage(int msgExtracted[4],char msg[STRLEN]);
void intToString(int n, char str[]);
void get_password(char* pass);
bool confirm_member();
char* createMessage(char Message[]);
int get_service_info();     //returns the size of the array


HWND WINAPI GetConsoleWindowNT();

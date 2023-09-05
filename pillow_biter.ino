#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

byte channel;

#define MAX_SSID 78 /* number of SSIDs */
char *ssids[MAX_SSID] = {
      "Mike Lindell is an idiot", 
      "MyPillow is filled with rocks",
      "Coupon Code: CrackHead77",

      "Dominion Votings Systems",
      "Clear Ballot Group",
      "Election Systems and Software",
      "MicroVote General Corp",
      "Unisyn Voting Solutions",
      "Hart InterCivic",

      "Dominion Votings Systems 2",
      "Clear Ballot Group 2",
      "Election Systems and Software 2",
      "MicroVote General Corp 2",
      "Unisyn Voting Solutions 2",
      "Hart InterCivic 2",

      "Dominion Votings Systems 3",
      "Clear Ballot Group 3",
      "Election Systems and Software 3",
      "MicroVote General Corp 3",
      "Unisyn Voting Solutions 3",
      "Hart InterCivic 3",

      "Dominion Votings Systems WAN",
      "Clear Ballot Group WAN",
      "Election Systems & Software WAN",
      "MicroVote General Corp WAN",
      "Unisyn Voting Solutions WAN",
      "Hart InterCivic WAN",

      "ClearVote 2.2",
      "ClearVote 2.3",
      "Democracy Suite 5.17",
      "Democracy Suite 5.5-C",
      "Democracy Suite 5.5-D",
      "EVS 6.0.3.0",
      "EVS 6.0.6.0",
      "EVS 6.1.1.0",
      "EVS 6.2.0.0",
      "EVS 6.3.0.0",
      "EVS 6.4.0.0",
      "MicroVote EMS 4.41 Voting",
      "OpenElect 2.2",
      "OpenElect 2.2.3",
      "Verity Voting 2.5",
      "Verity Voting 2.6",
      "Verity Voting 2.7",

      "ClearVote 2.2 5",
      "ClearVote 2.3 8",
      "Democracy Suite 5.17 8",
      "Democracy Suite 5.5-C 4",
      "Democracy Suite 5.5-D 7",
      "EVS 6.0.3.0 8",
      "EVS 6.0.6.0 10",
      "EVS 6.1.1.0 2",
      "EVS 6.2.0.0 4",
      "EVS 6.3.0.0 7",
      "EVS 6.4.0.0 8",
      "MicroVote EMS 4.41 Voting 6",
      "OpenElect 2.2 12",
      "OpenElect 2.2.3 2",
      "Verity Voting 2.5 6",
      "Verity Voting 2.6 7",
      "Verity Voting 2.7 9",
      
      "ClearVote 2.2 VPN",
      "ClearVote 2.3 WAN",
      "Democracy Suite 5.17 China",
      "Democracy Suite 5.5-C GOV-CIA",
      "Democracy Suite 5.5-D Internet",
      "EVS 6.0.3.0 WAN",
      "EVS 6.0.6.0 VPN",
      "EVS 6.1.1.0 China",
      "EVS 6.2.0.0 Router",
      "EVS 6.3.0.0 Cellular",
      "EVS 6.4.0.0 CIA",
      "MicroVote EMS 4.41 WAN Router",
      "OpenElect 2.2 China",
      "OpenElect 2.2.3 Tabulator 5",
      "Verity Voting 2.5 FBI",
      "Verity Voting 2.6 CIA",
      "Verity Voting 2.7 VPN"
      };

byte rnd;
byte i;
byte count;


byte wifipkt[128] = { 0x80, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                /*22*/  0xc0, 0x6c, 
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32*/  0x64, 0x00, 
                /*34*/  0x01, 0x04, 
                /* SSID */
                /*36*/  0x00};

byte pktsuffix[] = {
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                        0x04 };                       

void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
}

void loop() {

    wifipkt[10] = wifipkt[16] = random(256);
    wifipkt[11] = wifipkt[17] = random(256);
    wifipkt[12] = wifipkt[18] = random(256);
    wifipkt[13] = wifipkt[19] = random(256);
    wifipkt[14] = wifipkt[20] = random(256);
    wifipkt[15] = wifipkt[21] = random(256);

    count=37;

    rnd=random(MAX_SSID);
 
    wifipkt[count++]=strlen(ssids[rnd]);
    for (i=0; i<strlen(ssids[rnd]); i++) {
      wifipkt[count++]=ssids[rnd][i];
    }
    
    for (i=0; i<sizeof(pktsuffix); i++) {
       wifipkt[count++]=pktsuffix[i];
    }

    channel = random(1,12); 
    wifi_set_channel(channel);
    wifipkt[count-1] = channel;
    
    wifi_send_pkt_freedom(wifipkt, count, 0);
    wifi_send_pkt_freedom(wifipkt, count, 0);
    wifi_send_pkt_freedom(wifipkt, count, 0);
    delay(1);
}

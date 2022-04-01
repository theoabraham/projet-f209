#include <queue>
#include <string>
#include <iostream>

#include "../Quorridor/View/Interface/menuwindow.h"
#include "WindowNC.hpp"

using namespace std;

class Client {
 protected:
  int socket; 
  char gameMode[8] = "C\0";
  char numberPlayers[8] = "2\0";
  int line_counter=0;
private:
  
  Window *view; 

 protected:
  int handshake(string ip, int port, string pseudo, string mdp);
  static void* manageInputs(void* instance);
  virtual void manageInputs() = 0;
  virtual void manageSocketTraffic() = 0;

 public:
  Client() {}
  virtual ~Client() {}
};

class ClientNC : public Client
{
  WindowNC *view; 
  protected: 
      void manageInputs() override;
      void manageSocketTraffic() override;

  public:
    ClientNC() {view= new WindowNC();}
    virtual ~ClientNC() {delete view; }

    void runGame(string pseudo, string mdp, string ip, int port = 8080);
    void runMenu(string pseudo, string mdp, string ip, int port);
}; 

class ClientGUI : public Client
{
  WindowGUI *view; 
  protected: 
    void manageInputs() override {}
    void manageSocketTraffic() override {}
  public: 
    ClientGUI() {view = new WindowGUI();}
    virtual ~ClientGUI() {delete view; }

    void getMenu(){ view->getMenuWindow();}
}; 

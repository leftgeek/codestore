#ifndef SYNC_H
#define SYNC_H
#include "./headers/user.h"
class Sync{
private:
    UserModel* userModel;
    static Sync* sync;
    Sync();
public:
    ~Sync();
    static Sync* getSync();
    void syncCode();
    void setUser(UserModel* userModel);
    UserModel* getUser();
    bool isLogin();
    bool autoLogin();
};

#endif // SYNC_H

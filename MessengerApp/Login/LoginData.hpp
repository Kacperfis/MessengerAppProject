#pragma once
#include <string>

namespace login
{

struct LoginData
{
public:
    LoginData(const std::string& login, const std::string& password) : login_(login), password_(password){}
    LoginData(const LoginData& obj) = delete;
    LoginData(LoginData&& obj) = default;

    const std::string getLogin() { return login_; }
    const std::string getPassword(){ return password_; }

    LoginData& operator=(LoginData&& obj)
    {
        login_ = std::move(obj.login_);
        password_ = std::move(obj.password_);
        return *this;
    }
protected:
    std::string login_;
    std::string password_;
};

enum class loginStatus
{
    Logged,
    LoggedOut
};

} // namespace login

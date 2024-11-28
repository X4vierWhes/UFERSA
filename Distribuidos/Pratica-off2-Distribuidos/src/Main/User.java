package Main;

import java.io.Serializable;

public class User implements Serializable {

    private String login;
    private String password;

    public User(){
        this.login = "none";
        this.password = "none";
    }

    public User(String login, String password){
        setLogin(login);
        setPassword(password);
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}

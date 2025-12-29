#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const string BASE_PATH = "C:/xampp1/htdocs/ComplaintManagementWeb/data/";
const string MASTER_FILE = BASE_PATH + "complaint_data.txt";
const string ARCHIVE_FILE = BASE_PATH + "archive.txt";
const string ADMIN_FILE = BASE_PATH + "admin.txt";

/* ================= UTILS ================= */

string getDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%04d-%02d-%02d",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday);
    return string(buf);
}

string readPost() {
    int len = atoi(getenv("CONTENT_LENGTH"));
    string data(len, '\0');
    cin.read(&data[0], len);
    return data;
}

string getVal(const string &d, const string &k) {
    size_t p = d.find(k + "=");
    if (p == string::npos) return "";
    p += k.size() + 1;
    size_t e = d.find("&", p);
    if (e == string::npos) e = d.size();
    return d.substr(p, e - p);
}

/* ================= LOGIN ================= */

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \r\n\t");
    size_t end   = s.find_last_not_of(" \r\n\t");
    if (start == string::npos || end == string::npos) return "";
    return s.substr(start, end - start + 1);
}

bool checkAdmin(const string &u, const string &p) {
    ifstream in(ADMIN_FILE);
    if (!in.is_open()) return false;

    string line;
    getline(in, line);
    in.close();

    line = trim(line);
    string expected = trim(u + ":" + p);

    return line == expected;
}

bool deleteComplaintById(const string& targetId) {
    ifstream in(MASTER_FILE);
    ofstream temp(BASE_PATH + "temp.txt");
    ofstream archive(ARCHIVE_FILE, ios::app);

    if (!in.is_open() || !temp.is_open() || !archive.is_open())
        return false;

    string line;
    bool found = false;
    bool resolved = false;
    string block = "";

    while (getline(in, line)) {
        if (line.rfind("ID:", 0) == 0) {
            block = line + "\n";
            found = (line == "ID:" + targetId);
            resolved = false;
        } 
        else if (line == "---") {
            block += "---\n";

            if (found) {
                if (resolved) {
                    // save to archive
                    archive << "Deleted on: " << getDate() << "\n";
                    archive << block << "\n";
                } else {
                    // keep unresolved complaint
                    temp << block;
                }
            } else {
                temp << block;
            }
            block.clear();
            found = false;
        }
        else {
            block += line + "\n";
            if (found && line == "Status:Resolved")
                resolved = true;
        }
    }

    in.close();
    temp.close();
    archive.close();

    remove(MASTER_FILE.c_str());
    rename((BASE_PATH + "temp.txt").c_str(), MASTER_FILE.c_str());

    return true;
}

bool resolveComplaintById(const string& targetId) {
    ifstream in(MASTER_FILE);
    ofstream temp(BASE_PATH + "temp.txt");

    if (!in.is_open() || !temp.is_open())
        return false;

    string line;
    bool found = false;

    while (getline(in, line)) {
        if (line == "ID:" + targetId) {
            found = true;
            temp << line << "\n";
        }
        else if (found && line.rfind("Status:", 0) == 0) {
            temp << "Status:Resolved\n";
        }
        else {
            temp << line << "\n";
        }

        if (line == "---") {
            found = false;
        }
    }

    in.close();
    temp.close();

    remove(MASTER_FILE.c_str());
    rename((BASE_PATH + "temp.txt").c_str(), MASTER_FILE.c_str());

    return true;
}


/* ================= MAIN ================= */

int main() {
    string method = getenv("REQUEST_METHOD") ? getenv("REQUEST_METHOD") : "";

    /* ---------- POST ---------- */
    if (method == "POST") {
        string data = readPost();
        string action = getVal(data, "action");

        /* LOGIN */
        if (action == "login") {
            string u = getVal(data, "username");
            string p = getVal(data, "password");

            if (checkAdmin(u, p)) {
                cout << "Status: 303 See Other\r\n";
                cout << "Location: /ComplaintManagementWeb/frontend/admin_panel.html\r\n\r\n";
            } else {
                cout << "Content-Type: text/html\r\n\r\n";
                cout << "<h3>Invalid credentials</h3>";
            }
            return 0;
        }

        /* ADD COMPLAINT */
        if (action.empty()) {
            string name = getVal(data, "name");
            string phone = getVal(data, "phone");
            string email = getVal(data, "email");
            string content = getVal(data, "content");

            string date = getDate();
            string dailyFile = BASE_PATH + "complaints_" + date + ".txt";

            ofstream out(MASTER_FILE, ios::app);
            ofstream day(dailyFile, ios::app);

            out << "ID:" << time(0) << "\n";
            out << "Date:" << date << "\n";
            out << "Name:" << name << "\n";
            out << "Email:" << email << "\n";
            out << "Complaint:" << content << "\n";
            out << "Status:Pending\n---\n";

            day << "Name:" << name << " | " << content << "\n";

            out.close(); day.close();

            cout << "Status: 303 See Other\r\n";
            cout << "Location: /ComplaintManagementWeb/frontend/index.html\r\n\r\n";
            return 0;
        }

        /* RESOLVE */
        if (action == "resolve") {
            string id = getVal(data, "id");

            resolveComplaintById(id);

            cout << "Status: 303 See Other\r\n";
            cout << "Location: /ComplaintManagementWeb/frontend/admin_panel.html\r\n\r\n";
            return 0;
        }


        /* DELETE */
        if (action == "delete") {
            string id = getVal(data, "id");

            deleteComplaintById(id);

            cout << "Status: 303 See Other\r\n";
            cout << "Location: /ComplaintManagementWeb/frontend/admin_panel.html\r\n\r\n";
            return 0;
        }

    }

    /* ---------- GET (VIEW) ---------- */
    cout << "Content-Type: text/html\r\n\r\n";
    cout << "<pre>";
    ifstream in(MASTER_FILE);
    cout << in.rdbuf();
    in.close();
    cout << "</pre>";
    cout << "<a href='/ComplaintManagementWeb/frontend/admin_panel.html'>Back</a>";

    return 0;
}

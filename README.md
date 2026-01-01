# Complaint Management System (C++ CGI)
- A web-based Complaint Management System built using C++ (CGI) as the backend and HTML, CSS, and JavaScript as the frontend.  
- The system enables organizations to efficiently collect, manage, resolve, and archive complaints using a secure, role-based workflow.
- 
- This project demonstrates real-world backend logic, file-based data persistence, authentication, and input validation, making it suitable for academic, learning, and demonstration purposes.

## 🚀 Key Features

### User (Public)
- Submit complaints with strict validation
- Full name, valid phone number, valid email enforced
- Complaint must contain meaningful content (minimum word length)
- User-friendly interface with validation feedback

### Admin
- Secure admin login (file-based authentication)
- View all complaints
- Resolve complaints (status change)
- Delete complaints only after resolution
- Deleted complaints are archived (audit trail)
- Daily complaint logs generated automatically

# 🏢 Use Cases Across Different Organizations

- This system is generic and adaptable, meaning it can be used in many domains with minimal customization.

## 1️⃣ Educational Institutions (Colleges / Universities)

### Use Case:
- Students submit complaints related to:
  - Exam results
  - Faculty issues
  - Infrastructure problems
  - Hostel or mess facilities

### How it helps:
- Students submit complaints online
- Administration reviews and resolves complaints
- Resolved complaints are archived for future reference
- Daily logs help track complaint trends

### Example:
- A college IT department uses this system to manage student grievances transparently.

- 2️⃣ Corporate Organizations / Companies

- Use Case:
- Employees submit internal complaints such as:
  - HR issues
  - Workplace grievances
  - IT or infrastructure problems

- How it helps:
- Centralized complaint handling
- Role-based access ensures only admins can manage data
- Archived complaints maintain compliance records
- Daily logs support internal audits

- Example:
- A mid-sized company uses the system for internal employee grievance redressal.

- 3️⃣ Customer Support Departments

- Use Case:
- Customers submit complaints about:
  - Product defects
  - Service delays
  - Billing issues

- How it helps:
- Complaints are tracked from submission to resolution
- Only resolved complaints can be deleted (data safety)
- Historical records help analyze recurring issues

- Example:
- A local service provider uses this system as a lightweight customer support portal.

- 4️⃣ Government or Public Service Offices

- Use Case:
- Citizens submit complaints related to:
  - Municipal services
  - Public utilities
  - Documentation delays

- How it helps:
- Transparent complaint logging
- Admin-only authority prevents misuse
- Archived data ensures accountability
- Daily logs support reporting and audits

- Example:
- A municipal office deploys the system internally to track citizen complaints.

- 5️⃣ Hospitals and Healthcare Centers

- Use Case:
- Patients submit complaints about:
  - Appointment delays
  - Staff behavior
  - Facility issues

- How it helps:
- Organized complaint management
- Resolution tracking ensures service improvement
- Archived complaints support quality audits

- Example:
- A small clinic uses the system to improve patient feedback handling.

## 🛠️ Technology Stack

- Backend: C++ (CGI)
- Frontend: HTML, CSS, JavaScript
- Server: Apache (XAMPP for local execution)
- Data Storage: File-based (.txt)
- Authentication: File-based admin credentials
# Architecture Diagram

![System Architecture](docs/architecture.png)
# 📂 Project Structure
```bash
ComplaintManagementWeb
├── backend
│ └── complaint.cpp
├── frontend
│ ├── index.html
│ ├── add_complaint.html
│ ├── admin_login.html
│ ├── admin_panel.html
│ └── style.css
├── data
│ ├── admin.txt
│ ├── complaint_data.txt
│ ├── archive.txt
│ └── complaints_YYYY-MM-DD.txt
├── README.md
├──docs/
  └── architecture Diagram.png

```
## ▶️ How to Run (Local Setup)
```bash
1. Install XAMPP
2. Place the project inside: htdocs/ComplaintManagementWeb
3. Enable CGI module in Apache
4. Compile the backend: g++ backend/complaint.cpp -o cgi-bin/complaint.cgi
Open browser: http://localhost/ComplaintManagementWeb/frontend/index.html
```

## 🔐 Security & Validation

- Input validation on both frontend and backend
- Admin-only access for complaint management
- Deletion allowed only after resolution
- Archived complaints preserve data integrity

## 🎓 Academic Relevance
-
- This project demonstrates:
-  
- File handling in C++
- CGI-based web backend
- Role-based access control
- Real-world validation logic
- Clean separation of frontend and backend
- 
- It is suitable for:
-  
- Data Structures
- Web Technologies
- System Programming
- Mini / Major Projects
-  
- 👤 Author
- Abhishek Kale
- 
- 📌 Note
- This project uses C++ CGI, so it is intended for local or server-based Apache deployment and is not compatible with static hosting platforms.
  

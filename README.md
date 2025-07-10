# 🏨 Hotel Management System & Analysis

## Overview

This combined Hotel Management System is a full-featured solution to manage hotel operations, customer bookings, staff tasks, food ordering, and billing. It also includes an analytical dashboard that provides insights into bookings, profits, and room availability by processing data from an Oracle database through a modern web interface.

---

## 🎯 Features

### 🔒 Login Functionality

* Secure login for **customers** and **staff**.

### 🧑‍🤝‍🧑 Customer Management

* Register and manage customer information.
* View and book available hotel rooms.

### 👩‍💼 Staff Management

* Handle staff details, tasks, and logins.

### 🛏️ Room Booking

* Browse and reserve available hotel rooms.

### 🍽️ Food Ordering

* Order meals from the hotel menu.

### 💳 Billing

* Generate and display detailed bills for customers.

### 📊 Hotel Management Analysis

* Analyze booking data, room occupancy, and profits.
* Visual insights powered by Chart.js and data from an Oracle database.

---

## 🏗️ Class & File Structure

### Object-Oriented System

* **Customer**: Handles customer registration and bookings.
* **Staff**: Manages staff data and task allocation.
* **Food**: Manages menu items and food orders.
* **HotelRooms**: Handles room inventory and reservations.
* **LoginCustomer / LoginStaff**: Login logic for respective users.
* **Hotel**: Coordinates all major operations like food, billing, and room booking.

### Web-Based Analysis System

* `guest.html`: Add, view, and remove guest records.
* `index.html`: Dashboard showing booking and profit statistics.
* `sys.py`: Backend logic using Flask for handling requests and database operations.
* `Queries.txt`: SQL queries used in the backend.

---

## 🧰 Technologies Used

| Purpose               | Technology            |
| --------------------- | --------------------- |
| Backend               | Python 🐍     |
| Frontend              | HTML, JS, Chart.js 📊 |
| Database Connectivity | cx\_Oracle 🏛️        |
| Database              | Oracle Database 🗃️   |
| Object-Oriented Logic | C++ (OOP Concepts) 💻 |

---

## 🛠️ Installation & Usage

### 🔧 Step 1: Clone the Repositories

```bash
git clone https://github.com/chitwan6804/Hotel_Management.git
cd Hotel_Management
```

### ⚙️ Step 2: Install Dependencies

For the analysis system:

```bash
pip install -r requirements.txt
```

Ensure that the Oracle Database is installed and configured.

### 🚀 Step 3: Run the Applications

**Object-Oriented Management System**
Run your C++ application using your preferred compiler or IDE.

## 🤝 Contributing

We welcome contributions to both components of the system!

* Fork the repositories
* Create a feature branch
* Submit a pull request
* Feel free to open issues for any bugs or enhancements

---

## 📬 Contact

For any questions or suggestions, feel free to reach out through the GitHub issues or discussions tabs on the respective repositories.

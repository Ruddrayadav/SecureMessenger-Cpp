# 🔐 SecureMessenger-Cpp

A terminal-based secure messaging system written in C++. This simple app allows users to register, log in, send encrypted messages, and read their inbox. It uses a basic Caesar cipher for message encryption and stores data in text files.

---

## 🚀 Features

- 🔑 User registration and login system
- ✉️ Encrypted message sending using Caesar cipher
- 📥 Decryption and viewing of messages
- 🧠 Simple file-based user and message storage
- 🌈 Colored terminal interface (for better UX on Windows)

---

## 🛠 Tech Stack

- C++ (Standard Libraries)
- File I/O
- Windows-specific commands (for screen clearing and sleep)
- ANSI color codes for UI (CMD-friendly)

---

## 📂 Project Structure

SecureMessenger-Cpp/
│
├── main.cpp # Main source code
├── users.txt # Registered users (username password)
├── <username>_messages.txt # Each user's inbox (auto-generated)
├── README.md # Project documentation

---

## 🧪 How to Run

1. ⚙️ **Compile the Code**  
   Open CMD in your project folder and run:
   ```bash
   g++ main.cpp -o messenger.exe
   messenger.exe
▶️ Run the Program
 ```bash
    messenger.exe
 ```
💡 Note: This is Windows-specific due to the use of <windows.h>. For cross-platform use, you'll need to replace Sleep() and system("cls").
🔐 Message Encryption

This app uses a basic Caesar cipher:
```
ch += 3; // Encrypt
ch -= 3; // Decrypt
```
⚠️ Important: This is NOT suitable for real-world secure messaging. It's for learning purposes only.
🔮 Future Plans

Replace Caesar cipher with a stronger encryption (e.g., AES)
Cross-platform compatibility (Linux/macOS support)
Use file headers or a lightweight database for message management
Add GUI using Qt or web-based front-end
🤝 Contribution

Contributions are welcome! Feel free to fork, star ⭐, or open a pull request.

📜 License

MIT License – Use it freely and modify as you wish. Just give credit 🙂

👤 Author

Made with ❤️ by Rudra Yadav


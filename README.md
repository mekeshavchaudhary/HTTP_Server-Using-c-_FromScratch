# HTTP_Server-Using-c-_FromScratch
This code is a basic HTTP server written in C that listens on port 8080. It accepts HTTP GET requests and responds with a message. If the request URL contains a name parameter (e.g., GET /?name=John), the server responds with "Hello &lt;name>". Otherwise, it sends a default response, "Hello world."


Running the Code on Visual Studio Code (Mac)
Open Visual Studio Code.

Install GCC (if not already installed):

**1. Open your terminal in VS Code.**
Install GCC: brew install gcc.
Set Up the Project:

**2. Create a new file**, e.g., http_server.c, and paste the code into it.
Compile the Code:

**3.** In the terminal, navigate to the directory where the file is saved.
**Run the compilation command:**
bash
Copy code
gcc http_server.c -o http_server
Run the Server:

**4.** In the terminal,** start the server:**
bash
Copy code
./http_server
The server will run in the terminal and listen on port 8080.
Test the Server:

**5. Open a browser or use curl to send a request:**
bash
Copy code
curl "http://localhost:8080/?name=YourName"
You should see a response with "Hello YourName" if everything is working.
Let me know if you need more help with this!

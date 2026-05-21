from http.server import BaseHTTPRequestHandler, HTTPServer

latest = ""

class Handler(BaseHTTPRequestHandler):
    # assumes the data being sent is a string already in JSON format!
    def do_POST(self):
        # access global variable to store the data in, for do_GET
        global latest 
        
        # read data
        length = int(self.headers.get('Content-Length', 0))
        data = self.rfile.read(length).decode()

        latest = data

        print("Received:", data)

        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"OK")
        
    def do_GET(self):
        if self.path == "/latest":
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.send_header("Access-Control-Allow-Origin", "*") # enables CORS (Cross-Origin Resource Sharing) for JS frontend
            self.end_headers()

            # send data as bytes
            self.wfile.write(latest.encode())


server = HTTPServer(("0.0.0.0", 8000), Handler)
print("Server running on 8000")
server.serve_forever()
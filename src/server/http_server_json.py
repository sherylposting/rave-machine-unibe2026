from http.server import BaseHTTPRequestHandler, HTTPServer
import json

# receives values in csv format from ESP32, stores them in JSON format at localhost:8000/latest

latest = [0, 0, 0, 0, 0, 0]

class Handler(BaseHTTPRequestHandler):
    def do_POST(self):
        global latest

        length = int(self.headers.get('Content-Length', 0))
        data = self.rfile.read(length).decode()

        try:
            latest = [float(x) for x in data.split(",")]
        except:
            pass

        print("Received:", latest)

        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"OK")

    def do_GET(self):
        if self.path == "/latest":
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()

            self.wfile.write(json.dumps({
                "accX": latest[0],
                "accY": latest[1],
                "accZ": latest[2],
                "gyroX": latest[3],
                "gyroY": latest[4],
                "gyroZ": latest[5]
            }).encode())

server = HTTPServer(("0.0.0.0", 8000), Handler)
print("Server running on 8000")
server.serve_forever()
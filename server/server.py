import SimpleHTTPServer
import SocketServer
import CGIHTTPServer

PORT = 8000

Handler = CGIHTTPServer.CGIHTTPRequestHandler 

httpd = CGIHTTPServer.TCPServer(("", PORT), Handler)

print "serving at port", PORT
httpd.serve_forever()

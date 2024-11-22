import java.net.*;

public class UDPServer {
    public static void main(String[] args) {
        int port = 8080;
        byte[] buffer = new byte[1024];
        
        try (DatagramSocket socket = new DatagramSocket(port)) {
            System.out.println("UDP Server is waiting on port " + port);
            
            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                
                String message = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Message from client: " + message);
                
                String response = "Hello from UDP Server";
                byte[] responseBytes = response.getBytes();
                InetAddress clientAddress = packet.getAddress();
                int clientPort = packet.getPort();
                
                DatagramPacket responsePacket = new DatagramPacket(responseBytes, responseBytes.length, clientAddress, clientPort);
                socket.send(responsePacket);
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}

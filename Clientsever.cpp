HOST = ''
PORT = 6789

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((HOST, PORT))
    server_socket.listen()

    while True:
        connection_socket, client_address = server_socket.accept()
        with connection_socket:
            print('Connected by', client_address)
            while True:
                client_sentence = connection_socket.recv(1024).decode('utf-8')
                if not client_sentence:
                    break
                print('Received:', client_sentence)
                capitalized_sentence = client_sentence.upper() + '\n'
                connection_socket.sendall(capitalized_sentence.encode('utf-8'))

//Đây là đoạn mã Python tạo một server TCP lắng nghe kết nối đến trên cổng 6789.
//
//Dòng import socket được sử dụng để import module socket, cung cấp các chức năng giao tiếp mạng cấp thấp.
//
//Dòng tiếp theo HOST = '' thiết lập host là chuỗi rỗng, điều này có nghĩa là server sẽ lắng nghe kết nối đến trên bất kỳ giao diện mạng khả dụng nào.
//
//PORT = 6789 thiết lập số hiệu cổng mà server sẽ lắng nghe.
//
//Dòng with tiếp theo tạo một socket TCP sử dụng phương thức socket.socket(), có hai đối số: socket.AF_INET xác định đây là socket IPv4 và socket.SOCK_STREAM xác định đây là socket TCP.
//
//Dòng tiếp theo server_socket.bind((HOST, PORT)) liên kết socket server đến host và cổng đã chỉ định.
//
//server_socket.listen() đặt socket server vào chế độ lắng nghe, có nghĩa là nó sẽ chờ đợi kết nối đến.
//
//Vòng lặp while được sử dụng để lắng nghe kết nối đến từ client. Khi có kết nối, server_socket.accept() sẽ trả về một socket kết nối mới và địa chỉ của client đang kết nối.
//
//Với mỗi kết nối client, một vòng lặp while được sử dụng để nhận và xử lý các thông điệp gửi đến từ client. connection_socket.recv(1024).decode('utf-8') nhận một chuỗi tối đa 1024 byte từ client và chuyển đổi nó sang chuỗi unicode sử dụng utf-8.
//
//Nếu không có thông điệp được nhận từ client, vòng lặp sẽ kết thúc. Nếu có, server sẽ in ra thông điệp được nhận và trả lại cho client một phiên bản viết hoa của thông điệp đó, sử dụng connection_socket.sendall(capitalized_sentence.encode('utf-8')).

class TCPClient {
public static void main(String argv[]) throws Exception {
String sentence;
String modifiedSentence;
BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
Socket clientSocket = new Socket("127.0.0.1", 6789);
DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
sentence = inFromUser.readLine();
outToServer.writeBytes(sentence + '\n');
modifiedSentence = inFromServer.readLine();
System.out.println("FROM SERVER: " + modifiedSentence);
clientSocket.close();

//Dòng import socket được sử dụng để import module socket, cung cấp các chức năng giao tiếp mạng cấp thấp.
//
//Dòng tiếp theo tạo một socket client TCP sử dụng phương thức socket.socket(), có hai đối số: socket.AF_INET xác định đây là socket IPv4 và socket.SOCK_STREAM xác định đây là socket TCP.
//
//BufferedReader và DataOutputStream được sử dụng để nhận và gửi dữ liệu giữa client và server.
//
//Với mỗi kết nối client, dòng client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) tạo một socket client và kết nối đến server đang chạy trên localhost trên cổng 6789, sử dụng client_socket.connect(("127.0.0.1", 6789)).
//
//Dòng sentence = input("Enter a message: ") yêu cầu người dùng nhập vào một thông điệp để gửi đến server.
//
//outToServer.sendall(sentence.encode('utf-8')) gửi thông điệp đến server, sau đó modified_sentence = client_socket.recv(1024).decode('utf-8') nhận và chuyển đổi thông điệp viết hoa được trả về từ server.
//
//Cuối cùng, thông điệp được in ra bằng print("FROM SERVER:", modified_sentence).
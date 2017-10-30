### Thông tin cá nhân:
- Họ và tên: Võ Sỹ Liên Thành
- Sinh viên trường Đại học Khoa học tự nhiên - ĐHQG TP.HCM
- Khoa Công nghệ thông tin
- Chuyên ngành Kỹ thuật phần mềm

### Giới thiệu chung về project:

##### Game Sudoku là gì?:
Sudoku là một trò chơi với lưới ma trận ô vuông 9x9.
Nhiệm vụ của người chơi là điền các ô còn lại của lưới Sudoku với điều kiện:
- Mỗi hàng ngang phải có đầy đủ các số từ 1 - 9 không cần theo thứ tự.
- Mỗi cột phải có đầy đủ các số từ 1 - 9 không cần theo thứ tự.
- Mỗi vùng 3x3 phải có đầy đủ các số từ 1 - 9 không cần theo thứ tự.

##### Cách giải bài toán Sudoku:
- Dùng Backtracking (được sử dụng trong đồ án).
- Dùng các mẹo chơi gần như tượng tự Heuristic.

##### Các chức năng chính:
- Tạo màn chơi mới.
- Chơi tiếp màn chơi được lưu.
- Lưu màn đang chơi.
- Giải Sudoku, Sudoku dạng đường xuyên.
- Tạo lưới Sudoku xuất ra file text (Lưới Susoku được tạo chỉ có suy nhất một đáp án tránh nhập ngằn choi người chơi khi thi với nhau).
- Chọn độ khó khi chơi và khi tạo lưới Sudoku.
- Gợi ý một ô khi chơi.
- Kiểm tra các ô đã điền chính xác hay chưa.

##### Luồng xử lý ngoại lệ:
- Người chơi thao tác với phím không phải các phím chức năng sẽ bị quay về màn hình menu.
- Quá trình tạo lưới Sudoku tốn nhiều hơn thời gian cho phép sẽ hiện thông báo "Request timeout" và yêucầu người chơi thử lại.
- Nếu không đủ bộ nhớ chương trình sẽ hiện thông báo.

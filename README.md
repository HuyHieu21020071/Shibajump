# Shiba jump  
_Bài tập lớn môn lập trình nâng cao_
## Giới thiệu
Hello các bạn, mình tên là Hiệu. Mình làm game dựa trên game [DoodleJump](https://play.google.com/store/apps/details?id=com.lima.doodlejump&utm_source=web%20game&utm_medium=online&utm_campaign=html5_pilot) trên điện thoại
Ngôn ngữ mình sử dụng trong game là C++ và thư viện đồ họa SFML.
Mục tiêu: bạn phải di chuyển sao cho nhân vật của bạn đạt điểm cao nhất có thể. Game sẽ lưu lại số điểm cao nhất.
## Cách chơi 
Game có cách chơi đơn giản. Dùng hai phím mũi tên trái và phải để cho nhân vật rơi xuống platform, khi đó nhân vật sẽ được nhảy lên. Với mỗi lần nhảy lên cao hơn vị trí ban đầu, game sẽ cộng điểm vào điểm tổng. Khi nhân vật bị rơi xuống dưới màn hình của Game, bạn sẽ bị thua.
### Preview

![](image_ReadMe/ReadMe_1.png)

![](image_ReadMe/ReadMe_2.png)

![](image_ReadMe/ReadMe_3.png)

![](image_ReadMe/ReadMe_4.png)

## Thuật toán
 - Nhân vật và platform sẽ chứa một tọa độ và một gia tốc. Ban đầu, gia tốc của cả nhân vật và platform đều hướng xuống. Nếu nhân vật giao với platform, gia tốc của nhân vật sẽ được thay đổi hướng lên. Với mỗi Frame, gia tốc của nhân vật sẽ được giảm đi 0,2 và cập nhập lại vị trí bằng cách cộng tọa độ Y với gia tốc.
 - Khi nhân vật rơi xuống khỏi màn hình của game, bạn sẽ bị thua. Chương trình sẽ hiển thị màn hình thua và hai tùy chọn là quay trở về màn hình chính hay chơi lại game.
 - Game cũng chia ra thành các cấp độ. Cứ mỗi 1000 điểm, game sẽ tăng một cấp đọ. Mỗi cấp độ, số lượng platform sẽ ít đi khiến cho bạn phải di chuyển nhân vật cẩn thận hơn nếu không sẽ bị rơi.
## Đánh giá
### Em (Mình) xin tự đánh giá 9.25 điểm. ###
Em code lại game và bổ sung thêm nhiều tính năng dự trên hướng dẫn [Youtube](https://www.youtube.com/watch?v=7Vf_vQIUk5Q&list=PLB_ibvUSN7mzUffhiay5g5GUHyJRO4DYr&index=2) và đọc thêm các tài liệu của SFML trên trang chủ SFML. Mọi âm thanh, hình ảnh em đều tham khảo từ các nguồn trên mạng và design background bằng Canva.

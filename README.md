# HaNoi2017

Try hard!!!!!
# Construction 

Độ khó nghĩ: ☆☆☆ / Độ khó cài: ☆☆☆☆

## Tóm tắt đề bài 

Cho N thành phố trên mặt phẳng. Có 2 loại có thể xây:
- Đường bộ. Chỉ nối giữa 2 thành phố dọc / ngang và không đi qua hình chữ nhật cấm nào. Chi phí chính là độ dài của đường.
- Sân bay.

Với mỗi kế hoạch, chỉ có thể xây một số sân bay giới hạn, và mỗi kế hoạch có chi phí xây sân bay khác nhau.

Với mỗi kế hoạch tìm cách xây đường và sân bay có chi phí bé nhất để mỗi thành phố có đường đi đến một sân bay.

## Dựng đường bay

Hiển nhiên nếu có 3 thành phố A B C thẳng trên 1 đường ngang dọc, không cần dựng đường giữa thành phố A và C. 
Như vậy, dễ dàng chứng minh chỉ có tối đa 4N cạnh cần sử dụng. Ta sẽ liệt kê các cạnh này ra như nào?

Không giảm tính tổng quát, ta dựng các đường dọc. Xét các điểm nằm trên cùng đường dọc, ta sẽ dựng các đường đi giữa các điểm liên tiếp, và phải kiểm tra có hình chữ nhật nào nằm giữa đường đi của chúng hay không.

Việc này có thể dễ dàng xử lí bằng cách quét các hình chữ nhật từ trái sang phải, thêm các điểm mốc của tọa độ trên (để ý các hình chữ nhật không chứa các thành phố) ở tọa độ trái và xóa chúng đi ở các tọa độ phải. 

Việc dựng cạnh có thể thực hiện với độ phức tạp O(N log N).

## Tìm chi phí nhỏ nhất 

Xét kế hoạch có tối đa A sân bay với chi phí B.

- Hiển nhiên ta sẽ sử dụng nhiều cạnh có chi phí nhỏ hơn B nhất có thể. Để không sử dụng thừa, ta chỉ việc giữ dsu các thành phố đã liên thông, thêm các cạnh từ nhỏ đến lớn (giống như thuật toán cây khung).

Từ đây ta có các trường hợp sau:

- Nếu số thành phần liên thông không lớn hơn A: Ta xây một sân bay với mỗi thành phần liên thông là tối ưu.

- Nếu thêm tất cả cạnh mà số TPLT vẫn lớn hơn A: Kế hoạch này không thể thỏa mãn.

- Nếu có thể thêm để số TPLT xuống còn A: ta thêm các cạnh đó giống thuật toán trên, sau đó xây cả A sân bay.

Như vậy với mỗi truy vấn ta có thể giải trong O(N) (số cạnh là O(N)).

## Tính nhanh các truy vấn

Trước tiên, dễ dàng nhận ra ta luôn chỉ dùng tập cạnh được sử dụng trong cây khung. Gọi tập này là M.

Thứ hai, dễ dàng nhận ra chi phí để giảm số TPLT xuống N - x là x cạnh nhỏ nhất của tập M.

Như vậy, với mỗi truy vấn, ta có thể làm nhanh các công việc sau để tính giá trị của các TH bên trên:

- Tìm số cạnh chi phí bé hơn B: O(log N). Từ số cạnh tính được số TPLT.
- Tìm tổng x cạnh nhỏ nhất của tập: O(1). Dùng mảng tổng dồn.

Như vậy mỗi truy vấn có thể giải được trong O(log N).

Độ phức tạp của cả bài là O(N log N + Q log N).

# Mascots

Độ khó nghĩ: ☆☆☆ / Độ khó cài: ☆☆

## Tóm tắt đề bài

Cho bảng R x C có N ô đã điền trước. Tìm thứ tự điền các ô còn lại sao cho có nhiều lần nhất các ô đã điền tạo thành một hình chữ nhật kín.

## Phương pháp điền bảng

Không khó nhận ra phương pháp điền bảng tối ưu là như sau:
- Đầu tiên, điền ít nhất sao cho các điểm tạo thành một hình chữ nhật. Độ lớn hình chữ nhật chính là hình chữ nhật bao N điểm ban đầu.
- Nở hình chữ nhật này theo 1 trong 4 chiều, đến bao giờ hình chữ nhật phủ toàn bộ bảng.

Giả sử hình chữ nhật bao N điểm đầu là (a, b) => (c, d). Số cách điền bước 1 đơn giản là ((c - a + 1) * (d - b + 1) - N)!. Ta chỉ còn việc tìm số cách điền các phần còn lại.

## Quy hoạch động N^4

Ta có phương pháp quy hoạch động đơn giản sau:

Gọi f[a][b][c][d] là số cách điền để nở hình chữ nhật (a, b) => (c, d) thành hình chữ nhật phủ cả bảng.

Hiển nhiên f[1][1][R][C] = 1.

Công thức khá đơn giản:

```
f[a][b][c][d]	= f[a - 1][b][c][d] * (b - d + 1)! (với a > 1)
		+ f[a][b][c + 1][d] * (b - d + 1)! (với c < R)
		+ f[a][b - 1][c][d] * (c - a + 1)! (với b > 1)
		+ f[a][b][c][d + 1] * (c - a + 1)! (với d < C) 
```

Đáp số chính là f[a][b][c][d]. Tuy nhiên, độ phức tạp thuật toán này là O(N^4), chưa đủ AC.

## Thứ tự lựa chọn

Khi lựa chọn nở hình theo phương dọc, ta nhận ra rằng số cách chọn khi nở phía trên hay nở phía dưới không quan trọng. Đồng thời, cho dù thứ tự là gì, ta cũng luôn phải nở (a - 1) lần về phía trên và (R - b) lần về phía dưới.
Điều tương tự xảy ra với chiều ngang.

Như vậy, thay vì lựa chọn phía trên hay phía dưới ngay khi qhđ, ta có thể chỉ gọi nó là "phương dọc", sau đó chọn phía trên / dưới sau khi qhd. Số cách chọn chính là (a - 1)C(R - c + a - 1) (tổ hợp). Tương tự với chiều ngang.

Gọi F[w][l] là số cách nở hình chữ nhật w x l thành R x C.

- F[R][C] = 1.
- F[w][l] = F[w + 1][l] * l! + F[w][l + 1] * w!

Đáp số sẽ là F[c - a + 1][d - b + 1] * (a - 1)C(R - c + a - 1) * (b - 1)C(C - d + b - 1).

Độ phức tạp là O(N^2).

# Spy

Độ khó nghĩ: ☆☆☆ / Độ khó cài: ☆☆

## Tóm tắt đề bài

Cho 2 cây có hướng N đỉnh. Có M truy vấn, truy vấn thứ i phủ cây con gốc Ai trên cây 1 và cây con gốc Bi trên cây 2. Với mỗi số i, tính số truy vấn phủ cả đỉnh i trên cây 1 và đỉnh i trên cây 2.

## Euler Tour!

Vì N nhỏ, ta hoàn toàn có thể dựng một bảng P[][] có hàng là các đỉnh cây 1, cột là các đỉnh cây 2, sau đó mỗi truy vấn ta cộng tất cả các ô có hàng là nút thuộc cây con gốc Ai, cột là nút thuộc cây con gốc Bi. Sau đó, mỗi truy vấn ta chỉ cần lấy giá trị P[i][i].

Làm sao để có thể thực hiện việc cộng nhanh?

Trước tiên, ta cần phải làm cho các nút trong một cây con đứng cạnh nhau - như vậy truy vấn sẽ trở thành update 1 hình chữ nhật. Có 1 cách đơn giản để làm việc này: Dựng Euler Tour ở cả 2 cây.

## Update

Nhận thấy ta chỉ cần truy vấn điểm sau khi thực hiện tất cả truy vấn update hình chữ nhật, ta có thể dựng mảng cộng dồn.

Ban đầu P[i][j] = 0 với mọi i, j.

Với mỗi truy vấn update (a, b) => (c, d), ta:
- Tăng P[a][b] thêm 1
- Giảm P[c + 1][b] đi 1
- Giảm P[a][d + 1] đi 1
- Tăng P[c + 1][d + 1] thêm 1

Sau đó, truy vấn P[i][i] trở thành tính tổng (1, 1) => (i, i). Ta chỉ cần dựng mảng tổng dồn P rồi trả lời trong O(1).

Độ phức tạp là O(N^2 + M).

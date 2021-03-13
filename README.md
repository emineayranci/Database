# Database

Projede basit bir database yönetimi yapmaya çalıştım. Proje program.c, database.c ve kaydet.c olmak üzere 3 adet programdan oluşmaktadır.

Program.c dosyası sonsuz döngüde çalışarak kullanıcıdan sorgu alıyor. Sonrasında bu sorguyu named pipe ile database.c dosyasına gönderiyor. Database.c dosyası da sonsuz döngüde çalışarak named pipe ile aldığı sorguyu boşluğa göre parçalayarak sonucu program.c dosyasına named pipe ile geri gönderiyor. Eğer sorguda istenen veri kullanıcın belirttiği veri1.txt veya veri2.txt dosyalarında bulunamadıysa bulunamadı sonucu gönderilir.

Program.c dosyasında son olarak kullanıcıya “sorgu sonucu kaydedilsin mi?e/h” diye bir soru soruluyor ve cevap evet ise programdan fork->exec ile kaydet.c programı çalışıyor. Pipe ile kaydedilecek veri “kaydet.c” programına gönderiliyor. Kaydet.c programı gelen veriyi “sonuc.txt” dosyasına kaydediyor.

<img src="https://github.com/emineayranci/Database/blob/main/ekran%20g%C3%B6r%C3%BCnt%C3%BCs%C3%BC%201.PNG" width="500">

<img src="https://github.com/emineayranci/Database/blob/main/ekran%20g%C3%B6r%C3%BCnt%C3%BCs%C3%BC%202.PNG" width="500">



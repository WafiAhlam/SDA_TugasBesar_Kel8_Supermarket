RUN PROGRAM 
gcc main.c admin.c Avl.c items.c  NonBinaryTree.c TreeRak.c tumpukan.c Keranjang.c pelanggan.c -o main


Cara menggunakan sistem CHIKAFIKET 
pengguna dapat memilih 2 sistem sebagai admin dan pengguna 

ADMIN 

=========================
      MODE ADMIN
=========================
1. Login
2. Registrasi Admin Baru
0. Kembali ke Menu Utama
=========================  

1. Login 
masukan username yang sudah terdaftar jika akun sudah benar dan terdaftar maka user akan dapat masuk namun, jika tidak terdaftar maka pengguna akan gagal 

2. Registrasi Admin Baru 
pada menu ini user dapat mendaftarkan username dan juga password 

0. Kembali ke Menu Utama
pada menu ini user kembali ke menu utama


PELANGGAN 

=========================================
            MENU PELANGGAN
    Selamat datang, kas!
=========================================        
1. Lihat Peta & Isi Rak Supermarket
2. Ambil Barang dari Rak Promosi (POP from Stack)
3. Lihat Keranjang Belanja (Riwayat Pengambilan) 
0. Selesai Belanja (Checkout)
=========================================       

1. Lihat Peta & Isi Rak Supermarket
pelanggan dapat melihat rak dan juga isi rak supermarket

2. Ambil Barang dari Rak Promosi (POP from Stack)
pelanggan dapat mengambil produk pada rak promosi

3. Lihat Keranjang Belanja (Riwayat Pengambilan) 
pelanggan dapat melihat isi belanja yang telah yang dia ambil

0. Selesai Belanja (Checkout)
pelanggan dapat selesai dan men Checkout barang
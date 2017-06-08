# Tugas Besar 1 IF2211 Strategi Algoritma
## Kelompok 20 - Squilliams 
Erick Wijaya - 13515057

Adrian Mulyana - 13515075

William - 13515144

## Cara menjalankan program
1.Buka cmd pada folder bomberman yang sudah diinstall

v1.2.6/Game Engine/

2.Ketik command berikut pada cmd

Bomberman.exe --pretty -b "path menuju StrAlgo1-15057" "bot ke-1" "bot ke-n" (tambahkan -c "angka" bila ingin bermain dengan console)

3.Pastikan path menuju StrAlgo1-15057 benar sesuai tempat anda menyimpannya

4.Bila ingin mengganti identitas bot, cukup dengan mengubah isi bot.json

## Cara kompilasi program
g++ SampleBot.cpp Parse.cpp Map.cpp Player.cpp Bomb.cpp stdafx.cpp -o SampleBot -std=c++11

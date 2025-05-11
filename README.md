# qmk_nicola
QMKを親指シフト化する差分コード

## リポジトリのコードの使い方
- メインのQMKリポジトリをクローン。
- 利用するキーボードのKeymapsディレクトリ内にnicola.c, nicola.hを作成。
- nicola.cとのつなぎ方はlevinson.cの記述方法を確認すること。

## 設定している内容
- 英数モードに変更する場合に「d」キーと「f」キーを同時押し。
- 日本語入力モートに変更する場合は「j」キーと「k」キーを同時押し。

```c
return process_nicola(keycode, record, _NICOLA, KC_SPC, KC_MINS, mkeys);       // Nicola
```

keymaps.c内の最後の方の処理で`process_nicola`に渡す4番目と5番目の引数が左シフトと右シフトのキーになる。上記の例では

- 左シフト
    - KC_SPC - スペースキーが左の親指シフトキー。
- 右シフト
    - KC_MINS - 「-」マイナスキーが右の親指シフトキー。（左右セパレートのlevinsonキーボードで、私は右側の親指の位置に「-」キーを当てている）

のような設定になっている。ここは自由に変更できるはず。

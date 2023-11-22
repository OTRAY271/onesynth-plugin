# OneSynth Plugin

　OneSynthは，1つのつまみを直感的に操作するだけで無数の音色を作り出せるシンセサイザーです。OneSynth Pluginは，それをDAW上でエミュレートするVST/AUプラグインです。加えて，DAWがなくても動作するスタンドアロン版も提供しています。

- 現在開発中のベータ版であるため，インストールと使用は自己責任でお願いします。
- 開発途上であることに加えローカルのCPUで動作するよう性能を下げていることもあり，音色が思い通りにならないことが多々あるかと思いますが，あくまでも探索的なツールとしてお楽しみください。
- このプラグインは，DexedをForkして制作しました。

## 動作環境

- OS：Macのみ
- DAW：Logic，Reaper，Ableton Live

これらの条件を満たす場合でも動作しないことや不具合が発生することがあります。予めご了承ください。

## インストール

[インストーラー](https://drive.google.com/file/d/1tfW65xmUMKIeDCXskU21jUjJsQpjDDl-/view?usp=sharing)をダウンロード＆実行してください。スタンドアロン版とVST/AUプラグインが自動でインストールされます。

- pkgファイルを開く際に警告が表示される場合は，[こちらのページ](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)を参考に対処をお願いします。
- スタンドアロン版もしくはVST/AUプラグインを起動してから5分以上待っても画面が現れない場合は，動作対象外です。強制終了してください。

## 操作方法

1. スライダーを左右に動かして音色を探します。
2. 自分の欲しい音に少しでも近づいたらそこでYESボタンを押し，1に戻ります。
3. スライダーをどこに動かしても欲しい音に近づかなければNOボタンを押し，1に戻ります。

自分の欲しい音に十分近づくまで，1〜3を繰り返してください。

- LOADボタンを押すと，探索の初期地点としてプリセットが選べます。
- SAVEボタンを押すと，現在の音色をファイルに保存できます。
- 音が止まらなくなった場合は，PANICボタンを押してください。

## 既知の不具合

- ウィンドウを閉じてから再度開くと，音色は変わりませんがスライダーの位置が中央に戻ってしまいます。
- 入力した音に対して，出力される音のオクターブが異なってしまう場合があります。
- ピッチが不正確な音色が生成されることがあります。

## アンインストール

以下のファイルを削除してください。

`~/Library/Application Support/OneSynth`

`/Applications/OneSynth.app`

`~/Library/Audio/Plug-Ins/VST3/OneSynth.vst3`

`~/Library/Audio/Plug-Ins/Components/OneSynth.component`

## OneSynthについて

仕組みについては[ProtoPedia](https://protopedia.net/prototype/4346)をご覧ください。

## 謝辞

開発にあたり以下のOSS・手法を利用させていただきました。開発者の方々に感謝申し上げます。

https://github.com/asb2m10/dexed

https://github.com/nlohmann/json

https://github.com/gwendal-lv/spinvae

Le Vaillant, G., & Dutoit, T. (2023). Synthesizer Preset Interpolation Using Transformer Auto-Encoders. 2023 IEEE International Conference on Acoustics, Speech and Signal Processing (ICASSP), 1-5.

Chiu, C. H., Koyama, Y., Lai, Y. C., Igarashi, T., & Yue, Y. (2020). Human-in-the-loop differential subspace search in high-dimensional latent space. ACM Transactions on Graphics (TOG), 39(4), 85-1.
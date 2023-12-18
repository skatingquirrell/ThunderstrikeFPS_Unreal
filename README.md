# THUNDERSTRIKE

## 概要

サンダーストライクはUnreal Engineを使用して作成された小規模なFPSゲームであり、主にC++で実装されており、一部はBlueprintsを使用しています。プレイヤーは制限時間内に一連の敵を倒してデーモンゲートに到達する必要があります。

### [Youtube デモ動画](https://youtu.be/S-2DU25Tw7I)
[![デモビデオ](https://i3.ytimg.com/vi/S-2DU25Tw7I/maxresdefault.jpg)](http://www.youtube.com/watch?v=S-2DU25Tw7I "Thunderstrike Demo Video")


## 目次

1. [ゲームプレイ](#ゲームプレイ)
2. [コントロール](#コントロール)
3. [実装された機能](#実装された機能)
4. [インストール](#インストール)
5. [ライセンス](#ライセンス)

## ゲームプレイ

ゲームの主要な目的は、制限時間内に全てのヘルスポイントを失わずにデーモンゲートに到達することです。

## コントロール

- プレイヤーはWASDキーで移動し、マウスで照準を合わせることで、標準の一人称視点コントロールを使用します。
- スペースバーでジャンプします。
- 左クリックで射撃します。

## 実装された機能

このプロジェクトはC++で継承されたクラスとBlueprintsの組み合わせを使用して実装されました。基本的な学習目的でC++に焦点を当てています。

- **移動**: プレーヤーキャラクター（ヒーロー）と敵の移動を制御し、対応するアニメーションを行うためにC++プレーヤー継承クラスを使用しました。

  ![Movement](https://github.com/skatingquirrell/ThunderstrikeFPS_Unreal/blob/master/GIFs/Movement.gif)
  
- **アニメーション**: アイドル、チェイス、およびアタックポーズを含む敵のアニメーションをブレンドスペースで作成しました。
- **弾道**: 銃から発射される弾道を実装し、敵に命中した後または一定の時間が経過した後に自動的に破壊されます。

  ![Shoot](https://github.com/skatingquirrell/ThunderstrikeFPS_Unreal/blob/master/GIFs/ShootEnemy.gif)
  
- **敵AI**: AI Perception Componentを使用して、敵の感知能力を実装し、ヒーローを特定の可視範囲内で検出して追跡し、十分に近づくと攻撃し、ヒーローがその範囲外に出ると基本に戻ります。
  
  ![AI](https://github.com/skatingquirrell/ThunderstrikeFPS_Unreal/blob/master/GIFs/AI.gif)
  
- **衝突**: 敵が攻撃するとヒーローにダメージが与えられ、プロジェクタイルが敵に当たるとダメージが与えられます。
- **ユーザーインターフェース**: レベルのカウントダウンタイマーを表示し、時間切れ時にレベルを再起動します。ヒーローと敵のヘルス進捗バーを表示および更新します。ゲームオーバー時にレベルを再起動します。
- **目的地到達トリガー**: ヒーローがデーモンドアに到達したときにトリガーを作成し、3秒後にレベルを再起動します。

  ![Clear](https://github.com/skatingquirrell/ThunderstrikeFPS_Unreal/blob/master/GIFs/Clear.gif)
  
- **レベルデザイン**: マップ上に敵とオブジェクトを配置しました。Epicコンテンツを無料で利用することでプロセスを簡略化しました。

## インストール

- **必要なUnrealバージョン**: Unreal 5.3.2
- **必要な導入済みの無料コンテンツ（このGitリポジトリには個人的に開発したコンテンツのみが含まれています）**:
    - First Person Gameのスターターコンテンツ
    - [Infinity Blade: Castle](https://www.unrealengine.com/marketplace/en-US/product/infinity-blade-castle)
    - [Paragon: Aurora](https://www.unrealengine.com/marketplace/en-US/product/paragon-aurora)
    - [Paragon: Revenant](https://www.unrealengine.com/marketplace/en-US/product/paragon-revenant)
- Project Settings -> Project - Maps & Modeでのデフォルトのマップとポーン:
    - デフォルトゲームモード: BP_ThunderstrikeGameMode
    - デフォルトポーンクラス: BP_Hero

## ライセンス

Unreal Engine専用の使用許諾があります。カスタムライセンスなしでは、続編やリマスターの作成、または元のゲームをエミュレートすること、または元のゲームの商標、キャラクター名、その他のIPを使用して広告やゲームの名前を付けることはできません。

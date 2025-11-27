# 🆙 **Metroid Leveling - Demo -** 🆙

**Metroid Leveling** é a demo de um jogo com inspirações em **Hollow Knight** e na estética de **Solo Leveling**.

Você assume o papel de Helena uma mulher de 21 anos que quando ainda era recém-nascida acabou perdendo seus pais num grande desastre,
quando portais surgiram e abriram nos céus trazendo monstros com eles. Helena agora quer investigar os portais e você acompanhará o começo de sua jornada.

![Intro](assets\IntroParte1.png)

*Imagem gerada com IA*

## Você consegue sair vivo do portal mesmo Helena não tendo poderes?

![Intro](assets\IntroParte5.png)

*Imagem gerada com IA*

### Metroid Leveling foi desenvolvido em **C** utilizando a biblioteca gráfica **Raylib**

## 🛠️ Compilando

💻 **Instalação em Linux**

1. Certifique-se de ter o GCC, make e git:
   ```
   sudo apt install build-essential git
   ```

2. Instale todas as bibliotecas :
   ```
   sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
   ```

3. Baixe o código-fonte do Raylib diretamente do GitHub e entre na pasta:
   ```
   git clone --depth 1 https://github.com/raysan5/raylib.git raylib
   cd raylib/src/
   ```

4. Compilar a Raylib:
   ```
   make PLATFORM=PLATFORM_DESKTOP
   ```

5. Instalar a Raylib:
   ```
   sudo make install
   cd ~
   ```

6. Clone o repositório do jogo:
   ```
   git clone https://github.com/begnp/jogo_pif.git
   cd jogo_pif
   ```

7. Compilar o jogo:
   ```
   make run
   ```

Caso tenha qualquer problema consulte a documentação da [RayLib para Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

## 📜 Menu Principal

A tela de menu oferece as seguintes opções:

![Menu](assets\Menu_Jogo.png)

- 🟡 **Jogar**: Inicia o jogo.
- 🏆 **Ranking**: Visualiza os melhores tempos de quem concluiu o jogo.
- ⌨️ **Creditos**: Mostra os desenvolvedores do jogo.
- ❌ **Sair**: Fecha o jogo.

---

## 🕹️ Como Jogar

### Keybinds do jogo:

- Keybinds e suas funcionalidades:
  - **W** — Pular
  - **A** — Andar para a esquerda
  - **D** — Andar para a direita
  - **BARRA DE ESPAÇO** — Atacar
  - **ENTER** — (Para pular a intro do jogo)

---

## 🗺️ Estrutura do Mapa e Progressão

**Metroid Leveling** Possui 1 mapa com **5 áreas interconectadas**, desafiando o jogador com inimigos e elementos de plataforma.


### 🌀 Área 1 – Início do portal

- O jogador começa sua jornada numa especie de **Caverna** dentro de um portal, um ambiente com um ar pesado.
- É uma área introdutória onde o jogador deve **andar** para direita e encarar 2 **inimigos**.
- No final dessa área, o jogador encontrará a **entrada** para uma parte mais profunda da caverna.

---

### 🦇 Área 2 – Parte profunda da caverna

- Nessa área, o jogador encontrará **inimigos**, **plataformas** e entradas para outras **áreas**.
- Subindo as plataformas ele encontrará a **passagem** para a **área 3**.
- seguindo para a direita ele encontrará uma porta fechada e que leva para a área do **boss**.

---

### ⛏️ Área 3 – Parte superior da caverna

- Nessa área, o jogador encontrará mais **inimigos** e **plataformas**.
- Caso ele siga para a direita ele encontrará a **passagem** para a **área 4**.

---

### 🧌 Área 4 – Parte Superior direita da caverna (Ninho dos goblins)

- Nessa área, o jogador encontrará inumeros **inimigos** e **plataformas**
- Ele deve derrotar todos os **inimigos** para conseguir sair dali vivo.
- Após derrotar todos os inimigos ele conseguirá **finalmente sair** dessa área e a sala do boss é liberada.

---

###  Área Secreta – Parte escondida da Caverna

- Nessa área, o jogador encontrará um **item** que aumentará seu **dano**.
- Onde está? Bom se **atente aos detalhes** e talvez descubra.

---

### 👺 Desafio  – Derrotar 20 inimigos

- Os inimigos **respawnam** ao sair da área e voltar.
- Sem derrota-los, o jogador **não poderá sair do portal e zerar a demo**.
- O jogador deve ter cuidado, apesar de serem lentos e previsiveis um deslize e pode acabar morrendo.

---

**Explore e lute pela sua sobrevivência. A vida e o destino de Helena está em suas mãos, pronto para encarar Metroid Leveling?**

---

## Vídeo Demonstrativo

---

## 📊 Slides de apresentação do jogo

Confira os slides do nosso jogo:

[Slides no canva](https://www.canva.com/design/DAG52FNqzoU/cbrtNcsfOm-RGZ2SiHx_YA/edit?utm_content=DAG52FNqzoU&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

## 👥 Equipe de Desenvolvimento

- [**Arthur Reis**](https://github.com/queirozarthur) 
- [**Bernardo Guimarães**](https://github.com/begnp)
- [**Cauã Henrique**](https://github.com/CauaParente05)

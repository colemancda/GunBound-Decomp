# Localized strings (`Language.txt`)

Every dialog/message string in the client is looked up by **numeric id** from a
table built at startup by `LoadLocalizedStrings` (`0x43da00`) and read by
`GetLocalizedString` (`0x43dc70`). See ARCHITECTURE.md "Text localization" for
the subsystem and the id-block/caller map. This document is the **string
table itself**.

## What's actually in the shipped asset — important

- **Source**: the `Language.txt` entry inside `orig/graphics.xfs`, extracted
  and **checksum-verified** (`verify_checksum.py` → `MATCH`). Re-extract with:
  ```
  cd tools/lzhuf
  python3 -c "from extract_toc import read_toc; from decode_img import decode_entry_partial; \
    e=[x for x in read_toc('../../orig/graphics.xfs')[0] if x[0].lower()=='language.txt'][0]; \
    open('/tmp/Language.txt','wb').write(decode_entry_partial('../../orig/graphics.xfs',e[1],e[2],e[3],e[4],e[3]))"
  ```
- **The table is sparse.** This build defines **only ids 200–240** — the
  entire **error-dialog family**. Id 241 is present but **truncated** in the
  asset (`"Erro em Comprar\nNao…"` runs straight into ~16 KB of binary
  padding that fills out the entry's 20,242-byte decompressed size). Every
  *other* id the code requests (loading labels `0x320+`, HUD `0x27c+`, replay
  `0x1770+`, avatar-store `0xea6x`, …) is **not defined in this asset** — those
  UI elements are image/bitmap-driven in this build, and only the message-box
  dialogs are text-driven.
- **Language is Portuguese** (the GunBound.CA / Brazilian build). The client
  binary contains **no English text** — locale is entirely a function of which
  `Language.txt` a server packs. The **English column below is a translation**
  of the Portuguese, provided as a reading aid; it is **not** the original
  English wording an English (ijji/WC) server shipped. The Portuguese column is
  the verbatim ground truth.
- **Id ↔ error code**: `ShowErrorDialog(code)` resolves `id = code + 0xc7`
  (199). So the server-sent error code is `id − 199`, given in the second
  column. `<br>` marks a line break inside a message; a doubled `<br><br>` is
  the blank line between an error's title and its body.

## Error-dialog family (ids 200–240)

| id / code | Portuguese (verbatim from the asset) | English (translation) |
|---|---|---|
| 200 / 1 | Erro de Acesso do Servidor<br><br>Nao pode acessar o servidor que voce solicitou.<br>Por favor use outros servidores ou tente um pouco mais tarde. | Server Access Error<br><br>Cannot access the server you requested.<br>Please use other servers or try again a little later. |
| 201 / 2 | O tempo de acesso expirou.<br><br>Houve problema na rede ou o tempo de espera foi longo demais.<br>A conexao sera fechada automaticamente.<br>Por favor tente mais tarde. | Access time has expired.<br><br>There was a network problem or the wait was too long.<br>The connection will be closed automatically.<br>Please try again later. |
| 202 / 3 | Erro de funcao do Servidor<br>\O servidor nao consegue trabalhar adequadamente.<br>Por favor tente um  pouco mas tarde. | Server Function Error<br>The server cannot work properly.<br>Please try again a little later. |
| 203 / 4 | Erro de funcao do Servidor<br>Houve erros devido a funcionalidade do servidor.<br>Por favor tentar um pouco mais tarde. | Server Function Error<br>There were errors due to server functionality.<br>Please try again a little later. |
| 204 / 5 | Reinicie o Servidor!<br><br>LEMBRE-SE DESSA REGRA: Voce precisa reiniciar o servidor toda vez que criar uma nova conta para jogar! | Restart the Server!<br><br>REMEMBER THIS RULE: You must restart the server every time you create a new account to play! |
| 205 / 6 | Erro de Login<br><br>Senha errada.<br>Por favor checar sua senha. | Login Error<br><br>Wrong password.<br>Please check your password. |
| 206 / 7 | Erro de Login<br>Seu Login nao pode ser usada neste servidor.<br>Por favor usar os servidores que servem seu pais. | Login Error<br>Your login cannot be used on this server.<br>Please use the servers that serve your country. |
| 207 / 8 | Deve estar VAZIO!!! | Must be EMPTY!!! *(placeholder/reserved slot)* |
| 208 / 9 | Erro Interno de Dados<br><br>Os dados internos foram alterados.<br>Por favor reiniciar o GunBound. | Internal Data Error<br><br>The internal data was altered.<br>Please restart GunBound. |
| 209 / 10 | Erro de acesso de canal<br><br>Excesso de usuarios no canal.<br>Por favor tente conectar em canal diferente. | Channel Access Error<br><br>Too many users in the channel.<br>Please try connecting to a different channel. |
| 210 / 11 | Erro de criacao de canal<br><br>Nao pode criar mais canais.<br>Por favor utilize os canais existentes. | Channel Creation Error<br><br>Cannot create more channels.<br>Please use the existing channels. |
| 211 / 12 | Erro de acesso de canal<br><br>Voce ja esta dentro do canal. | Channel Access Error<br><br>You are already inside the channel. |
| 212 / 13 | Erro de Acesso de Sala de Jogo<br><br>Excesso de usuarios na sala.<br>Por favor tente conectar numa sala diferente. | Game Room Access Error<br><br>Too many users in the room.<br>Please try connecting to a different room. |
| 213 / 14 | Erro de Criacao de Sala de Jogo<br><br>Sala de jogo nao pode ser criada.<br>Por favor use a sala existente. | Game Room Creation Error<br><br>The game room cannot be created.<br>Please use the existing room. |
| 214 / 15 | Erro de Entrada em Sala de Jogo<br><br>Voce ja esta dentro da sala. | Game Room Entry Error<br><br>You are already inside the room. |
| 215 / 16 | Sala de Jogo Bloqueada<br><br>A sala esta em jogo.<br>Voce nao pode entrar. | Game Room Locked<br><br>The room is in a match.<br>You cannot enter. |
| 216 / 17 | Erro de Inicializacao de Jogo<br><br><br>Ainda nao esta preparada para iniciar.. | Game Start Error<br><br><br>It is not ready to start yet.. |
| 217 / 18 | Conexao do Servidor fechada<br><br>Houve tentativa de um outro usuario utilizar o mesmo Login.<br>A conexao foi encerrada. | Server Connection Closed<br><br>Another user attempted to use the same login.<br>The connection was terminated. |
| 218 / 19 | Erro de Comunicacao<br><br>Impossivel de comunicar ou convidar outros, devido a erro em sistema de comunidade. | Communication Error<br><br>Unable to communicate with or invite others, due to an error in the community system. |
| 219 / 20 | Acesso Proibido<br><br>Este Login e  proibido<br>Conexao encerrada. | Access Forbidden<br><br>This login is forbidden<br>Connection terminated. |
| 220 / 21 | Erro de Versao<br><br>Versao diferente.<br>Conexao encerrada<br> Tente reinstalar, ou verificar atualizacoes. | Version Error<br><br>Different version.<br>Connection terminated<br>Try reinstalling, or check for updates. |
| 221 / 22 | Loging Error<br><br>Login nao autorizado.<br>Por favor registre um outro Login novamente. | Login Error *(sic: "Loging")*<br><br>Login not authorized.<br>Please register another login again. |
| 222 / 23 | Conexao com o Servidor Encerrada<br><br>Conexao de jogo de %s sera proibida.<br>Conexao encerrada. | Server Connection Terminated<br><br>Game connection from %s will be forbidden.<br>Connection terminated. *(`%s` = a name)* |
| 223 / 24 | Conexao com o Servidor Encerrada. | Connection to the Server Terminated. |
| 224 / 25 | Modificacao de dados<br><br>Arquivo importante foi modificado.<br>Aplicacao se encerrando. | Data Modification<br><br>An important file was modified.<br>Application shutting down. |
| 225 / 26 | O Programa Interferiu<br><br>Escrever a mesma palavra varias vezes pode prejudicar outras.<br>Uso frequente das mesmas palavras(spammer) pode resultar na perda do Login.<br> Jogo foi encerrado. | Interference Detected<br><br>Writing the same word many times can harm others.<br>Frequent use of the same words (spamming) can result in loss of the login.<br>The game was terminated. |
| 226 / 27 | Erro de Compra.<br><br>Nao ha Ouro ou Cash(dinheiro) suficiente.<br>Por favor comprar items diferentes. | Purchase Error.<br><br>Not enough Gold or Cash.<br>Please buy different items. |
| 227 / 28 | Erro de Dados Internos.<br><br>Os dados internos foram modificados.<br>Por favor reinicie o Jogo GunBound. | Internal Data Error.<br><br>The internal data was modified.<br>Please restart the GunBound game. |
| 228 / 29 | Acesso ao Servidor esta Proibido<br><br>O Servidor Selecionado e limitado por niveis.<br>Por favor usar diferentes servidores. | Server Access is Forbidden<br><br>The selected server is level-limited.<br>Please use different servers. |
| 229 / 30 | Acesso ao Servidor esta Proibido<br><br>O Servidor Selecionado e apenas para membros da liga.<br>Por favor usar servidores diferentes. | Server Access is Forbidden<br><br>The selected server is for league members only.<br>Please use different servers. |
| 230 / 31 | Acesso ao Servidor esta Proibido<br><br>O servidor selecionado e somente para nao-membros da liga.<br>Por favor usar servidores diferentes. | Server Access is Forbidden<br><br>The selected server is for non-league members only.<br>Please use different servers. |
| 231 / 32 | Acesso ao Servidor esta Proibido<br><br>Sua liga nao pode acessar este servidor.<br>Por favor usar servidores diferentes. | Server Access is Forbidden<br><br>Your league cannot access this server.<br>Please use different servers. |
| 232 / 33 | Erro na hora de dar presente.<br><br> O Login nao existe.<br>Por favor verificar o Login utilizado. | Error while sending a gift.<br><br>The login does not exist.<br>Please verify the login used. |
| 233 / 34 | Erro de Venda<br><br>Nao se pode Vender itens comprados.. | Sale Error<br><br>Purchased items cannot be sold.. |
| 234 / 35 | Erro de Venda<br><br>Nao se pode vender itens de evento. | Sale Error<br><br>Event items cannot be sold. |
| 235 / 36 | Erro de Venda<br><br>Nao se pode vender itens recebidos. | Sale Error<br><br>Received items cannot be sold. |
| 236 / 37 | Erro em dar presente<br><br>Nao se pode dar items ganhos de presente. | Gift Error<br><br>Items that were won cannot be given as gifts. |
| 237 / 38 | Erro de Doacao<br><br>Tentou enviar itens nao existentes.<br>Por favor tentar novamente. | Donation Error<br><br>Attempted to send non-existent items.<br>Please try again. |
| 238 / 39 | Enviando doacoes<br><br>O presente nao pode ser enviada. | Sending donations<br><br>The gift could not be sent. |
| 239 / 40 | Erro de Comunicacao<br><br>A comunicacao nao esta sendo feita adequadamente. Jogo fechado. | Communication Error<br><br>Communication is not working properly. Game closed. |
| 240 / 41 | Erro de Comunicacao<br><br>A comunicacao de dados nao esta sendo feita adequadamente.<br>Por favor reinicie o GunBound.<br>Jogo encerrado. | Communication Error<br><br>Data communication is not working properly.<br>Please restart GunBound.<br>Game terminated. |
| 241 / 42 | Erro em Comprar<br>Nao… *(truncated in the asset — message runs into binary padding)* | Purchase Error<br>No… *(truncated)* |

## Ids the code requests but this asset does not define

The client's `GetLocalizedString` call sites reference several other id blocks
(see ARCHITECTURE.md "Text localization" → the id-block map): WinMain
`0x12d–0x142`/`0x7530–0x753b`, packet notices `0x19a–0x19e`, battle events
`0x25c–0x274`, HUD `0x27c–0x340`, loading `0x320–0x32f`, room-list
`0x4e20–0x4e23`, replay `0x1770–0x177f`, avatar-store `0xea60–0xea6d`. **None
of these are present** in this build's `Language.txt` — only ids 200–240 are.
Documenting their strings would require a more complete (or English)
`Language.txt` from another GunBound distribution; the values are not
recoverable from the assets in this repo.

# Rede Social - Trabalho em Equipe

## Integrantes
- Alan Prates
- Daniel Monteiro
- Danilo Silveira
- Paulo Pereira

## Descrição da Atividade
Este projeto consiste na implementação de uma rede social baseada no Twitter, chamada X. A rede social terá funcionalidades básicas, como a capacidade de criar perfis de usuário, postar tweets (apenas texto até 255 caracteres), seguir outros usuários e receber feeds de tweets de pessoas que você segue.

### Funcionalidades Principais:
- Os usuários podem se registrar na rede social, especificando um nome de usuário único e seu nome real.
- Os usuários podem postar tweets.
- Os usuários podem seguir outros usuários.
- Os usuários podem ver um feed de tweets dos usuários que estão seguindo.
- Os tweets devem ser exibidos em ordem cronológica, com os mais recentes no topo.

### Classes Implementadas:
- `Usuario`: Representa os usuários da rede social. Cada usuário tem um nome de usuário único, um nome real, uma lista de seguidores e uma lista de pessoas que ele segue.
- `Tweet`: Representa os tweets postados pelos usuários. Cada tweet tem um autor, um conteúdo de texto e uma data de criação.
- `RedeSocial`: Responsável por gerenciar todos os usuários e tweets na rede social.

### Instruções de Uso
1. Clone o repositório em sua máquina local.
2. Compile e execute o programa em um ambiente compatível com C++.
3. Siga as opções do menu para criar contas, postar tweets, seguir usuários, ver feeds e salvar dados.

### Organização do Repositório
- `main.cpp`: Contém a implementação do programa principal.
- `README.md`: Este arquivo com informações sobre o projeto.
- `dados.txt`: Arquivo para armazenar os dados da rede social.

### Como Contribuir
- Faça um fork do repositório.
- Crie um branch para implementar novas funcionalidades ou corrigir problemas.
- Envie um pull request com suas contribuições.

### Licença
Este projeto está sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para obter mais detalhes.

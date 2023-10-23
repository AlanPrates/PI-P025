#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
class Usuario {
private:
   string nome_usuario;
    string nome;
    vector<Usuario*> seguidores;
    vector<Usuario*> seguindo;
    vector<string> tweets;

public:
    Usuario(string nome_usuario, string nome) : nome_usuario(nome_usuario), nome(nome) {}

    void postar_tweet(string tweet) {
        tweets.push_back(tweet);
    }

    void seguir(Usuario* usuario) {
        seguindo.push_back(usuario);
        usuario->adicionar_seguidor(this);
    }

    void adicionar_seguidor(Usuario* usuario) {
        seguidores.push_back(usuario);
    }

    vector<string> receber_feed() {
        vector<string> feed;
        for (Usuario* u : seguindo) {
            for (string tweet : u->tweets) {
                feed.push_back(u->get_nome() + ": " + tweet);
            }
        }
        return feed;
    }

    string get_nome() {
        return nome;
    }

    string get_nome_usuario() {
        return nome_usuario;
    }

    vector<string> get_tweets() {
        return tweets;
    }

    vector<Usuario*> get_seguidores() {
        return seguidores;
    }

    vector<Usuario*> get_seguindo() {
        return seguindo;
    }
};

class Tweet {
private:
    Usuario* autor;
    string conteudo;

public:
    Tweet(Usuario* autor, string conteudo) : autor(autor), conteudo(conteudo) {}

    string get_autor() {
        return autor->get_nome();
    }

    string get_conteudo() {
        return conteudo;
    }
};

class RedeSocial {
private:
    vector<Usuario*> usuarios;
    vector<Tweet*> tweets;

public:
    ~RedeSocial() {
        for (Usuario* u : usuarios) {
            delete u;
        }
        for (Tweet* t : tweets) {
            delete t;
        }
    }

    void registrar_usuario(string nome_usuario, string nome) {
        usuarios.push_back(new Usuario(nome_usuario, nome));
    }

    Usuario* buscar_usuario(string nome_usuario) {
        for (Usuario* u : usuarios) {
            if (u->get_nome_usuario() == nome_usuario) {
                return u;
            }
        }
        return nullptr;
    }

    vector<Usuario*> listar_usuarios() {
        return usuarios;
    }

    vector<Tweet*> listar_tweets() {
        return tweets;
    }

    void postar_tweet(Usuario* autor, string conteudo) {
        Tweet* tweet = new Tweet(autor, conteudo);
        tweets.push_back(tweet);
        autor->postar_tweet(conteudo);
    }

    void seguir(Usuario* seguidor, Usuario* seguindo) {
        seguidor->seguir(seguindo);
    }

    void salvar_dados() {
        ofstream arquivo("dados.txt");

        for (Usuario* u : usuarios) {
            arquivo << u->get_nome_usuario() << " " << u->get_nome() << endl;

            for (string tweet : u->get_tweets()) {
                arquivo << "Tweet: " << u->get_nome_usuario() << " " << tweet << endl;
            }
        }

        arquivo.close();
    }

    void carregar_dados() {
        ifstream arquivo("dados.txt");
        string linha;

        while (getline(arquivo, linha)) {
            if (linha.find("Tweet: ") == 0) {
                string nome_usuario = linha.substr(7, linha.find(" ", 7) - 7);
                string conteudo = linha.substr(linha.find(" ", 7) + 1);

                Usuario* autor = buscar_usuario(nome_usuario);
                if (autor != nullptr) {
                    postar_tweet(autor, conteudo);
                }
            } else {
                string nome_usuario = linha.substr(0, linha.find(" "));
                string nome = linha.substr(linha.find(" ") + 1);

                registrar_usuario(nome_usuario, nome);
            }
        }

        arquivo.close();
    }

    void mostrar_seguidos(Usuario* usuario) {
        vector<Usuario*> seguidos = usuario->get_seguindo();
        cout << "Usuários seguidos por " << usuario->get_nome() << ":" << endl;
        for (Usuario* u : seguidos) {
            cout << u->get_nome() << endl;
        }
    }

    void mostrar_seguidores(Usuario* usuario) {
        vector<Usuario*> seguidores = usuario->get_seguidores();
        cout << "Seguidores de " << usuario->get_nome() << ":" << endl;
        for (Usuario* u : seguidores) {
            cout << u->get_nome() << endl;
        }
    }
};

void mostrar_menu() {
    cout << "===== Menu =====" << endl;
    cout << "1. Criar conta" << endl;
    cout << "2. Postar tweet" << endl;
    cout << "3. Seguir usuário" << endl;
    cout << "4. Ver feed" << endl;
    cout << "5. Ver seguidos" << endl;
    cout << "6. Ver seguidores" << endl;
    cout << "7. Salvar dados" << endl;
    cout << "8. Sair" << endl;
    cout << "================" << endl;
}

int main() {
    RedeSocial rede_social;
    rede_social.carregar_dados(); // Carrega os dados do arquivo

    int escolha;

    do {
        mostrar_menu();
        cout << "Escolha uma opção: ";
        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (escolha) {
            case 1: {
                string nome_usuario, nome;
                cout << "Digite um nome de usuário: ";
                cin >> nome_usuario;
                cout << "Digite seu nome: ";
                cin >> nome;
                rede_social.registrar_usuario(nome_usuario, nome);
                cout << "Conta criada com sucesso!" << endl;
                break;
            }
            case 2: {
                string nome_usuario, tweet;
                cout << "Digite seu nome de usuário: ";
                cin >> nome_usuario;
                Usuario* autor = rede_social.buscar_usuario(nome_usuario);
                if (autor != nullptr) {
                    cin.ignore();
                    cout << "Digite o tweet (até 255 caracteres): ";
                    getline(cin, tweet);
                    if (tweet.length() <= 255) {
                        rede_social.postar_tweet(autor, tweet);
                        cout << "Tweet postado com sucesso!" << endl;
                    } else {
                        cout << "O tweet deve ter no máximo 255 caracteres." << endl;
                    }
                } else {
                    cout << "Usuário não encontrado." << endl;
                }
                break;
            }
            case 3: {
                string seguidor, seguindo;
                cout << "Digite o nome de usuário do seguidor: ";
                cin >> seguidor;
                cout << "Digite o nome de usuário do usuário a ser seguido: ";
                cin >> seguindo;
                Usuario* seguidor_ptr = rede_social.buscar_usuario(seguidor);
                Usuario* seguindo_ptr = rede_social.buscar_usuario(seguindo);
                if (seguidor_ptr != nullptr && seguindo_ptr != nullptr) {
                    rede_social.seguir(seguidor_ptr, seguindo_ptr);
                    cout << "Usuário seguido com sucesso!" << endl;
                } else {
                    cout << "Usuário(s) não encontrado(s)." << endl;
                }
                break;
            }
            case 4: {
                string nome_usuario;
                cout << "Digite seu nome de usuário: ";
                cin >> nome_usuario;
                Usuario* usuario = rede_social.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    cout << "Feed de " << usuario->get_nome() << ":" << endl;
                    for (string tweet : usuario->get_tweets()) {
                        cout << tweet << endl;
                    }
                } else {
                    cout << "Usuário não encontrado." << endl;
                }
                break;
            }


            case 5: {
                string nome_usuario;
                cout << "Digite seu nome de usuário: ";
                cin >> nome_usuario;
                Usuario* usuario = rede_social.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    rede_social.mostrar_seguidos(usuario);
                } else {
                    cout << "Usuário não encontrado." << endl;
                }
                break;
            }
            case 6: {
                string nome_usuario;
                cout << "Digite seu nome de usuário: ";
                cin >> nome_usuario;
                Usuario* usuario = rede_social.buscar_usuario(nome_usuario);
                if (usuario != nullptr) {
                    rede_social.mostrar_seguidores(usuario);
                } else {
                    cout << "Usuário não encontrado." << endl;
                }
                break;
            }
            case 7: {
                rede_social.salvar_dados();
                cout << "Dados salvos com sucesso!" << endl;
                break;
            }
            case 8:
                break;
            default:
                cout << "Opção inválida. Por favor, escolha novamente." << endl;
        }

    } while (escolha != 8);

    return 0;
}

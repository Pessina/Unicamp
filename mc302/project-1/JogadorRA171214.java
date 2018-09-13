
/*

   Felipe Sousa Pessina RA:171214

                O algoritmo utilizado para o JogadorRA171214 se baseia em basicamente 5 etapas, alternando entre os modos de jogo OFENSIVO, CONTROLE e CURVA
            MANA.
    	        Para alternar entre cada modo, são realizadas algumas verificações que serão discutidas abaixo juntamente com a implementação utilizada para
    	    cada momento
                    Etapa 1:
                        Ao iniciar meu turno eu verifico se o maior dano que eu posso causar no meu oponente é suficiente para matá-lo. Caso seja possível,
                        o modo OFENSIVO é ativado, e causo o maior dano no meu oponente, matando-o.
                        A estratégia para o uso de cartas neste modo é a seguinte:
                            Como o meu dano de magias e ataque é suficiente para matar o oponente, eu não baixo lacaios
                            Para o uso de magias, encontra-se a primeira combinação que possui dano suficiente, somado ao ataque que mate o oponente, essa
                            combinação é utilizada
                            Os ataques dos lacaios são todos direcionados ao inimigo
                    Etapa 2:
                        Caso não seja possível matar meu oponente com meu maior dano, o algoritmo verifica se o dano dos lacaios do meu oponente é suficiente
                    para me matar no próximo turno. Caso seja possível, a estratégia é reduzir ao máximo o dano do meu oponente, mesmo que seja necessário
                    realizar trocas desfavoráveis.
                        A estratégia para o uso de cartas neste modo é a seguinte:
                        Como o dano do oponente é suficiente para me matar, eu procuro na lista das jogadas possiveis do turno, a jogada que melhor ira
                        reduzir o dano do oponente, mesmo que eu faça troca desfavoravel, e uso não compensativo de magias
                        Caso sobre mana eu baixo lacaios com a mana restante, para otimizar o uso da mana e melhorar a minha mesa
                    Caso nenhuma das duas situações anteriores venha a ocorrer, o jogo entra em um estágio que chamo de "estável", niguém pode se matar.
                    Então a verificação é baseada nas possibilidades de troca favorável.
                    Etapa 3:
                        Se houver uma situação em que a troca seja favorável para mim, eu irei iniciar a troca ativando o modo CONTROLE, aumentando ao máximo
                    a diferença entre o meu dano e o dano do meu oponente, de tal que forma que eu aumente minha vantagem.
                        A estratégia para o uso de cartas neste modo é a seguinte:
                            Primeiramente eu utilizo magias e ataque de lacaios para realizar a troca favoravel
                            Se sobrar para baixar lacaios, eu os baixo de tal forma que eu maximize o meu ataque
                    Etapa 4:
                        Caso não existam trocas favoráveis, o modo CURVA MANA é ativado, nele eu priorizo baixar lacaios fortes para diminuir a vantagem do
                    oponente, e se possível uso magias para matar os lacaios do oponente se possível. Como a troca é desfavorável nesta situação, eu ataco
                    com todos os meus lacaios o oponente, e deixo que ele inicie a troca caso ele queira.
                        A estratégia para o uso de cartas neste modo é a seguinte:
                            Primeiramente eu ataco com meus lacaios o oponente e baixo os lacaios com custo de mana alto
                            Se sobrar mana, eu utilizo magias para matar os lacaios do oponente, de acordo com as regras do modo CURVA MANA
                    Etapa 5:
                        Este modo é ativado quando as condições do enunciado para o modo CONTROLE e modo CURVA MANA não são satisfeitas, então eu apenas baixo
                    os lacaios e ataco com o meu maior dano o meu oponente
                    No final de cada etapa, eu verifico se a mana é maior do que 2, se for eu utilizo o poder heroico contra o oponente
	            Este basicamente é o funcionamento de cada modo de jogo, e como alterno entre eles. E para otimizar o uso de mandar, e cada troca antes de
	        inicializar os algoritmos de verificação de modo, o JogadorRA171214, faz as combinatórias das possibilidades de ataque, magias e baixar lacaios
	        para escolher a melhor para o momento otimizando o uso de mana, reduzir a vida do oponente e controlar a mesa.

 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

/**
 * Esta classe representa um Jogador aleatório (realiza jogadas de maneira aleatória) para o jogo LaMa (Lacaios & Magias).
 * @see java.lang.Object
 * @author Rafael Arakaki - MC302
 */
public class JogadorRA171214 extends Jogador {
    private ArrayList<CartaLacaio> lacaios;
    private ArrayList<CartaLacaio> lacaiosOponente;
    private static final int MODO_CONTROLE = 0;
    private static final int MODO_CURVA_MANA = 1;
    private static final int MODO_GENERICO = 2; //Modo padrão do jogo, de forma a não infringir as regras básicas
    private static int minhaMana;
    private static int vidaOponente;
    private static int vidaOponenteCopia;
    /**
     * O método construtor do JogadorAleatorio.
     *
     * @param maoInicial Contém a mão inicial do jogador. Deve conter o número de cartas correto dependendo se esta classe Jogador que está sendo construída é o primeiro ou o segundo jogador da partida.
     * @param primeiro   Informa se esta classe Jogador que está sendo construída é o primeiro jogador a iniciar nesta jogada (true) ou se é o segundo jogador (false).
     */
    public JogadorRA171214(ArrayList<Carta> maoInicial, boolean primeiro) {
        primeiroJogador = primeiro;

        mao = maoInicial;
        lacaios = new ArrayList<>();
        lacaiosOponente = new ArrayList<>();

    }

    /**
     * Um método que processa o turno de cada jogador. Este método deve retornar as jogadas do Jogador decididas para o turno atual (ArrayList de Jogada).
     *
     * @param mesa            O "estado do jogo" imediatamente antes do início do turno corrente. Este objeto de mesa contém todas as informações 'públicas' do jogo (lacaios vivos e suas vidas, vida dos heróis, etc).
     * @param cartaComprada   A carta que o Jogador recebeu neste turno (comprada do Baralho). Obs: pode ser null se o Baralho estiver vazio ou o Jogador possuir mais de 10 cartas na mão.
     * @param jogadasOponente Um ArrayList de Jogada que foram os movimentos utilizados pelo oponente no último turno, em ordem.
     * @return um ArrayList com as Jogadas decididas
     */
    public ArrayList<Jogada> processarTurno(Mesa mesa, Carta cartaComprada, ArrayList<Jogada> jogadasOponente) {

        if (cartaComprada != null)
            mao.add(cartaComprada);
        int minhaVida;
        if (primeiroJogador) {
            minhaMana = mesa.getManaJog1();
            minhaVida = mesa.getVidaHeroi1();
            vidaOponente = mesa.getVidaHeroi2();
            vidaOponenteCopia = vidaOponente;
            lacaios = mesa.getLacaiosJog1();
            lacaiosOponente = mesa.getLacaiosJog2();
        } else {
            minhaMana = mesa.getManaJog2();
            minhaVida = mesa.getVidaHeroi2();
            vidaOponente = mesa.getVidaHeroi1();
            vidaOponenteCopia = vidaOponente;
            lacaios = mesa.getLacaiosJog2();
            lacaiosOponente = mesa.getLacaiosJog1();
        }

        class CustomComparator implements Comparator<Carta> {
            public int compare(Carta carta1, Carta carta2) {
                return (carta2.getMana() - carta1.getMana());
            }
        }

        /* Organiza a mão do jogador em ordem decrescente de mana */
        mao.sort(new CustomComparator());

        ArrayList<Jogada> minhasJogadas = new ArrayList<>();

        /* Copia o vetor de lacaios e lacaiosOponente, para salvar os estados iniciais do lacaio ao iniciar o turno. */

        ArrayList <CartaLacaio> lacaiosCopia = new ArrayList<>();
        ArrayList <CartaLacaio> lacaiosOponenteCopia = new ArrayList<>();

        for (CartaLacaio lacaio1 : lacaios) {
            lacaiosCopia.add(new CartaLacaio(lacaio1.getID(),
                    lacaio1.getNome(),
                    lacaio1.getMana(),
                    lacaio1.getAtaque(),
                    lacaio1.getVidaAtual(),
                    lacaio1.getVidaMaxima(),
                    lacaio1.getEfeito(),
                    lacaio1.getTurno()));
        }

        for (CartaLacaio aLacaiosOponente : lacaiosOponente) {
            lacaiosOponenteCopia.add(new CartaLacaio(aLacaiosOponente.getID(),
                    aLacaiosOponente.getNome(),
                    aLacaiosOponente.getMana(),
                    aLacaiosOponente.getAtaque(),
                    aLacaiosOponente.getVidaAtual(),
                    aLacaiosOponente.getVidaMaxima(),
                    aLacaiosOponente.getEfeito(),
                    aLacaiosOponente.getTurno()));
        }

        /* Separa a mão do jogador em cartas de magias e lacaios */

        ArrayList<Carta> cartasMagias = new ArrayList<>();

        for (Carta aMao : mao) {
            if (aMao instanceof CartaMagia && aMao.getMana() <= minhaMana) {
                cartasMagias.add(aMao);
            }
        }

        ArrayList<Carta> cartasLacaio= new ArrayList<>();

        for (Carta aMao : mao) {
            if (aMao instanceof CartaLacaio && aMao.getMana() <= minhaMana) {
                cartasLacaio.add(aMao);
            }
        }

       /* Gera todas as combinaçoes de ataque para cada lacaio, e depois uma combinatória para gerar todos os ataques possiveis no turno */

        ArrayList <ArrayList <UsoCarta>> listaAtaqueLacaios = new ArrayList<>(); //Armazena em cada coluna, todos os ataques que cada lacaio pode realizar
        ArrayList<UsoCarta> combinacaoAtaqueAtual = new ArrayList<>(); //Armazena a atual combinação, entre os ataques de cada lacaio
        ArrayList<ArrayList <UsoCarta>> combinacoesAtaques = new ArrayList<>(); //Aramazena todas as combinações de ataques para o turno


        for (CartaLacaio lacaio : lacaios) {
            ArrayList<UsoCarta> lacaioAtaquesPossiveis = new ArrayList<>();
            for (CartaLacaio lacaioOponente : lacaiosOponente) {
                lacaioAtaquesPossiveis.add(new UsoCarta(lacaio, lacaioOponente));
            }
            lacaioAtaquesPossiveis.add(new UsoCarta(lacaio, null));
            listaAtaqueLacaios.add(lacaioAtaquesPossiveis);
        }

        if (listaAtaqueLacaios.size() > 0)
            combinatoriaUsoCartas(listaAtaqueLacaios, combinacaoAtaqueAtual, combinacoesAtaques, 0);

        /* Gera todas as combinacoes de uso para cada magia, e depois uma combinatoria para gerar todos os usos possiveis no turno */

        ArrayList <ArrayList <UsoCarta>> listaMagiasUso = new ArrayList<>(); //Armazena em cada coluna, todos os alvos que cada magia ter
        ArrayList<UsoCarta> combinacaoUsoMagiaAtual = new ArrayList<>(); //Armazena a combinação atual entre os alvos de cada magia
        ArrayList<ArrayList <UsoCarta>> combinacoesUsoMagias = new ArrayList<>(); //Armazena todas as combinações de magias


        for (Carta cartaMagia : cartasMagias) {
            ArrayList<UsoCarta> magiaUsosPossiveis = new ArrayList<>();
            if (((CartaMagia) cartaMagia).getMagiaTipo() == TipoMagia.BUFF) {
                if (lacaios.size() != 0) {
                    int alvo = 0;
                    for (int k = 0; k < lacaios.size(); k++) {
                        if (lacaios.get(k).getVidaAtual() >= lacaios.get(alvo).getVidaAtual()) {
                            if (lacaios.get(k).getVidaAtual() == lacaios.get(alvo).getVidaAtual()) {
                                if (lacaios.get(k).getAtaque() > lacaios.get(alvo).getAtaque()) {
                                    alvo = k;
                                }
                            } else {
                                alvo = k;
                            }
                        }
                    }
                    magiaUsosPossiveis.add(new UsoCarta(cartaMagia, lacaios.get(alvo)));
                }
            } else if (((CartaMagia) cartaMagia).getMagiaTipo() == TipoMagia.AREA) {
                magiaUsosPossiveis.add(new UsoCarta(cartaMagia, null));
            } else {
                for (CartaLacaio lacaioOponente : lacaiosOponente) {
                    if (((CartaMagia) cartaMagia).getMagiaTipo() == TipoMagia.ALVO) {
                        magiaUsosPossiveis.add(new UsoCarta(cartaMagia, lacaioOponente));
                    }
                }
                magiaUsosPossiveis.add(new UsoCarta(cartaMagia, null));
            }
            listaMagiasUso.add(magiaUsosPossiveis);
        }

        ArrayList <ArrayList <UsoCarta>> listaMagiaUsoCopia = new ArrayList<>(listaMagiasUso);

        for (int i = 0; i<listaMagiasUso.size(); i++) {
            combinatoriaColunasArrayList(listaMagiasUso, i, 0, combinacaoUsoMagiaAtual, combinacoesUsoMagias, 0);
            listaMagiasUso = new ArrayList<> (listaMagiaUsoCopia);
        }

        verificarCustoManaUsoCartaValido(combinacoesUsoMagias);

        Collections.reverse(combinacoesUsoMagias);

        /* Gera todas as possibilidades para baixar lacaios no turno */

        ArrayList <Carta> listaLacaios= new ArrayList<>(cartasLacaio); //Armazena os lacaios que podem ser jogados
        ArrayList<ArrayList <Carta>> combinacoesLacaios= new ArrayList<>(); //Armazena todas as combinações de lacaios que podem ser jogados no turno

        ArrayList <Carta> listaLacaiosCopia = new ArrayList<>(listaLacaios);

        for (int i = 0; i<listaLacaios.size(); i++) {
            combinatoriaColunasArrayList(listaLacaios, i, 0, combinacoesLacaios);
            listaLacaios = new ArrayList<> (listaLacaiosCopia);
        }

        verificarCustoManaCartaValido(combinacoesLacaios);

        Collections.reverse(combinacoesLacaios);

        /* Calcula o maior dano que posso causar no meu oponente, utilizando magia e ataques. Se for possivel mata-lo eu o faço
         * MODO ATAQUE */

        int danoTotalMeu;

        int meuDanoInicialLacaios = calculcarDanoLacaios (lacaios);

        int maiorDanoMagia = 0;
        int indexMaiorDanoMagia = 0;

        for (int i = 0; i<combinacoesUsoMagias.size(); i++) {
            boolean somenteAlvoOponente = true;
            int danoJogada = 0;
            for (int j = 0; j < combinacoesUsoMagias.get(i).size(); j++) {
                CartaMagia cartaUsada = (CartaMagia) combinacoesUsoMagias.get(i).get(j).getCartaUsada();
                Carta cartaAlvo= combinacoesUsoMagias.get(i).get(j).getCartaAlvo();
                if (cartaAlvo != null) {
                    boolean alvoLacaioBuff = false;
                    for (CartaLacaio lacaio : lacaios) {
                        if (cartaAlvo == lacaio) {
                            alvoLacaioBuff = true;
                            danoJogada += cartaUsada.getMagiaDano();
                            break;
                        }
                    }
                    if (!alvoLacaioBuff) {
                        somenteAlvoOponente = false;
                        break;
                    }
                }
                else {
                    danoJogada += cartaUsada.getMagiaDano();
                }
            }
            if (somenteAlvoOponente) {
                if (danoJogada > maiorDanoMagia) {
                    maiorDanoMagia = danoJogada;
                    indexMaiorDanoMagia = i;
                }
            }
        }

        if (minhaMana >= 2)
            danoTotalMeu = maiorDanoMagia + meuDanoInicialLacaios + 1;
        else
            danoTotalMeu = maiorDanoMagia + meuDanoInicialLacaios;

        if (danoTotalMeu >= vidaOponente) {

            for (CartaLacaio lacaio : lacaios) {
                Jogada jogada = new Jogada(TipoJogada.ATAQUE, lacaio, null);
                minhasJogadas.add(jogada);
            }

            if (combinacoesUsoMagias.size() > 0) {
                jogadaMagiaEAtaque(combinacoesUsoMagias, indexMaiorDanoMagia, mao, minhasJogadas);
                minhaMana -= calcularCustoManaUsoCarta(combinacoesUsoMagias.get(indexMaiorDanoMagia));
            }
            poderHeroico(minhasJogadas);
            return minhasJogadas;
        }

        /* Calcula o maior dano que meu oponente pode me causar, se ele for maior que minha vida, eu uso de todos os recursos para reduzir
        o dano do meu oponente, mesmo que as trocas seja desfavoráveis
        MODO CONTROLE DESFAVORAVEL*/

        int oponenteDanoInicialLacaios = calculcarDanoLacaios (lacaiosOponente);

        int menorDanoOponenteFinal = 0;
        int maiorDanoMeuFinal = 0;
        int menorCustoManaFinal = 0;
        int indexMelhorJogadaDiminuiDanoOponente = 0;

        ArrayList <ArrayList<UsoCarta>> combinacoesJogadas = new ArrayList<>();

        resetaLacaios(lacaios, lacaiosOponente, lacaiosCopia, lacaiosOponenteCopia);

        /* Concatena as possibilidades de uso de magias e de magias, para criar todas as possibilidades de jogada que causam dano */
        for (int i = 0; i<combinacoesAtaques.size(); i++) {
            if (combinacoesUsoMagias.size() > 0) {
                for (ArrayList<UsoCarta> combinacaoUsoMagia : combinacoesUsoMagias) {
                    ArrayList<UsoCarta> combinacaoAtual = new ArrayList<>(combinacaoUsoMagia);
                    combinacaoAtual.addAll(combinacoesAtaques.get(i));
                    if (verificaJogadaValida(combinacaoAtual, MODO_GENERICO, lacaiosOponente)) {
                        combinacoesJogadas.add(combinacaoAtual);
                    }
                    resetaLacaios(lacaios, lacaiosOponente, lacaiosCopia, lacaiosOponenteCopia);
                }
            }
            else if (combinacoesAtaques.size() > 0) {
                if (verificaJogadaValida(combinacoesAtaques.get(i), MODO_GENERICO, lacaiosOponente)) {
                    combinacoesJogadas.add(combinacoesAtaques.get(i));
                }
                resetaLacaios(lacaios, lacaiosOponente, lacaiosCopia, lacaiosOponenteCopia);
            }
        }

        if (oponenteDanoInicialLacaios >= minhaVida) {


            /* Processa as jogadas para encontrar a melhor */
            if (combinacoesJogadas.size() > 0) {
                for (int i = 0; i < combinacoesJogadas.size(); i++) {

                    processarJogada(combinacoesJogadas.get(i), lacaiosOponente);

                    int danoMeu = calculcarDanoLacaios(lacaios);
                    int danoOponente = calculcarDanoLacaios(lacaiosOponente);
                    int custoMana = calcularCustoManaUsoCarta(combinacoesJogadas.get(i));

                    if (danoOponente <= menorDanoOponenteFinal) {
                        if (danoOponente == menorDanoOponenteFinal) {
                            if (danoMeu >= maiorDanoMeuFinal) {
                                if (danoMeu == maiorDanoMeuFinal) {
                                    if (custoMana <= menorCustoManaFinal) {
                                        menorCustoManaFinal = custoMana;
                                        indexMelhorJogadaDiminuiDanoOponente = i;
                                    }
                                } else {
                                    maiorDanoMeuFinal = danoMeu;
                                    indexMelhorJogadaDiminuiDanoOponente = i;
                                }
                            }
                        } else {
                            menorDanoOponenteFinal = danoOponente;
                            indexMelhorJogadaDiminuiDanoOponente = i;
                        }
                    }

                    resetaLacaios(lacaios, lacaiosOponente, lacaiosCopia, lacaiosOponenteCopia);
                }

                jogadaMagiaEAtaque(combinacoesJogadas, indexMelhorJogadaDiminuiDanoOponente, mao, minhasJogadas);
                minhaMana -= calcularCustoManaUsoCarta(combinacoesJogadas.get(indexMelhorJogadaDiminuiDanoOponente));
                verificarCustoManaCartaValido(combinacoesLacaios);
            }

            verificaNumeroLacaios(combinacoesLacaios, lacaios);
            int indexMelhorCombinacaoLacaios= melhorCombincaoLacaios(combinacoesLacaios, MODO_CURVA_MANA);
            if (indexMelhorCombinacaoLacaios != -1) {
                int custoManaLacaios = calcularCustoManaCarta(combinacoesLacaios.get(indexMelhorCombinacaoLacaios));
                minhaMana -= custoManaLacaios;
                jogadaLacaio(combinacoesLacaios, indexMelhorCombinacaoLacaios, mao, minhasJogadas);
            }
            poderHeroico(minhasJogadas);
            return minhasJogadas;
        }

        /* Como o eu não mato o oponente e nem o oponente me mata o jogo esta em um estágio "estável"
        então este algoritmo avalia qual a melhor jogada para o jogo optando entre o modo CURVA_MANA e o modo CONTROLE */

        int indexMelhorJogadaDiferencaDano = 0;
        boolean jogadaFavoravel = false;
        int maiorDiferencaDanoFinalEInicial = -3000;
        int maiorDiferencaVida = -3000;


        if (danoTotalMeu < vidaOponente && oponenteDanoInicialLacaios < minhaVida) {

            ArrayList<ArrayList<UsoCarta>> combinacoesJogadasControle = new ArrayList<>();

            for (ArrayList<UsoCarta> jogadaAtual : combinacoesJogadas) {
                if (verificaJogadaValida(jogadaAtual, MODO_CONTROLE, lacaiosOponente)) {
                    combinacoesJogadasControle.add(jogadaAtual);
                }
            }

            /* Processa as jogadas para encontrar a melhor */
            if (combinacoesJogadasControle.size() > 0) {

                for (int i = 0; i < combinacoesJogadasControle.size(); i++) {

                    processarJogada(combinacoesJogadasControle.get(i), lacaiosOponente);

                    int danoMeu = calculcarDanoLacaios(lacaios);
                    int danoOponente = calculcarDanoLacaios(lacaiosOponente);

                    int diferencaDanoInicial = meuDanoInicialLacaios - oponenteDanoInicialLacaios;
                    int diferencaDanoFinal = danoMeu - danoOponente;

                    int diferencaDanoFinalEInicial = diferencaDanoFinal - diferencaDanoInicial;
                    int diferencaVida = vidaOponenteCopia - vidaOponente;

                    if (diferencaDanoFinalEInicial > 0) {
                        jogadaFavoravel = true;
                        if (diferencaDanoFinalEInicial >= maiorDiferencaDanoFinalEInicial) {
                            if (diferencaDanoFinal == maiorDiferencaDanoFinalEInicial) {
                                if (diferencaVida > maiorDiferencaVida) {
                                    maiorDiferencaVida = diferencaVida;
                                    indexMelhorJogadaDiferencaDano = i;
                                }
                            } else {
                                maiorDiferencaDanoFinalEInicial = diferencaDanoFinalEInicial;
                                indexMelhorJogadaDiferencaDano = i;
                            }
                        }
                    }

                    resetaLacaios(lacaios, lacaiosOponente, lacaiosCopia, lacaiosOponenteCopia);
                }

               /* Caso haja jogada favoravel inicia a troca, para aumentar a diferenca entre o meu dano e o dano do oponente
               * MODO CONTROLE FAVORAVEL*/

                if (jogadaFavoravel) {
                    minhaMana -= calcularCustoManaUsoCarta(combinacoesJogadasControle.get(indexMelhorJogadaDiferencaDano));
                    jogadaMagiaEAtaque(combinacoesJogadasControle, indexMelhorJogadaDiferencaDano, mao, minhasJogadas);
                    verificarCustoManaCartaValido(combinacoesLacaios);

                    verificaNumeroLacaios(combinacoesLacaios, lacaios);
                    int indexMelhorCombinacaoLacaios = melhorCombincaoLacaios(combinacoesLacaios, MODO_CONTROLE);
                    if (indexMelhorCombinacaoLacaios != -1) {
                        int custoManaLacaios = calcularCustoManaCarta(combinacoesLacaios.get(indexMelhorCombinacaoLacaios));
                        minhaMana -= custoManaLacaios;
                        jogadaLacaio(combinacoesLacaios, indexMelhorCombinacaoLacaios, mao, minhasJogadas);
                    }
                    poderHeroico(minhasJogadas);
                    return minhasJogadas;
                }
            }

            /* Caso não hajam trocas favoraveis, eu baixo lacaios fortes, uso magias para reduzir o dano do oponente e ataco diretamente com os lacaios
            deixando para o meu oponente iniciar a troca
            MODO CURVA MANA*/

            verificaNumeroLacaios(combinacoesLacaios, lacaios);
            int indexMelhorCombinacaoLacaios = melhorCombincaoLacaios(combinacoesLacaios, MODO_CURVA_MANA);
            if (indexMelhorCombinacaoLacaios != -1) {
                int custoManaLacaios = calcularCustoManaCarta(combinacoesLacaios.get(indexMelhorCombinacaoLacaios));
                minhaMana -= custoManaLacaios;
                jogadaLacaio(combinacoesLacaios, indexMelhorCombinacaoLacaios, mao, minhasJogadas);
            }

            for (CartaLacaio lacaio : lacaios) {
                Jogada jogada = new Jogada(TipoJogada.ATAQUE, lacaio, null);
                minhasJogadas.add(jogada);
            }

            verificarCustoManaUsoCartaValido(combinacoesUsoMagias);

            if (combinacoesUsoMagias.size() > 0) {

                ArrayList<ArrayList<UsoCarta>> combinacoesValidasJogadasCurvaMana = new ArrayList<>();

                for (ArrayList<UsoCarta> jogadaAtual : combinacoesUsoMagias) {
                    if (verificaJogadaValida(jogadaAtual, MODO_CURVA_MANA, lacaiosOponente)) {
                        combinacoesValidasJogadasCurvaMana.add(jogadaAtual);
                    }
                }

                /* Processa as jogadas para encontrar a melhor */
                if (combinacoesValidasJogadasCurvaMana.size() > 0) {

                    for (int i = 0; i < combinacoesValidasJogadasCurvaMana.size(); i++) {
                        processarJogada(combinacoesValidasJogadasCurvaMana.get(i), lacaiosOponente);

                        int danoMeu = calculcarDanoLacaios(lacaios);
                        int danoOponente = calculcarDanoLacaios(lacaiosOponente);

                        int diferencaDanoInicial = meuDanoInicialLacaios - oponenteDanoInicialLacaios;
                        int diferencaDanoFinal = danoMeu - danoOponente;

                        int diferencaDanoFinalEInicial = diferencaDanoFinal - diferencaDanoInicial;
                        int diferencaVida = vidaOponenteCopia - vidaOponente;

                        if (diferencaDanoFinalEInicial > 0) {
                            if (diferencaDanoFinalEInicial >= maiorDiferencaDanoFinalEInicial) {
                                if (diferencaDanoFinal == maiorDiferencaDanoFinalEInicial) {
                                    if (diferencaVida > maiorDiferencaVida) {
                                        maiorDiferencaVida = diferencaVida;
                                        indexMelhorJogadaDiferencaDano = i;
                                    }
                                } else {
                                    maiorDiferencaDanoFinalEInicial = diferencaDanoFinalEInicial;
                                    indexMelhorJogadaDiferencaDano = i;
                                }
                            }
                        }
                        resetaLacaios(lacaios, lacaiosOponente, lacaiosCopia, lacaiosOponenteCopia);
                    }
                }
                jogadaMagiaEAtaque(combinacoesUsoMagias, indexMelhorJogadaDiferencaDano, mao, minhasJogadas);
                minhaMana -= calcularCustoManaUsoCarta(combinacoesUsoMagias.get(indexMelhorJogadaDiferencaDano));
                poderHeroico(minhasJogadas);
                return minhasJogadas;
            }
        }

        /* Caso não hajam jogadavas validas CONTROLE ou CURVA MANA, eu apenas ataco com os lacaios e baixo novos
        * MODO ATAQUE */
        poderHeroico(minhasJogadas);
        return minhasJogadas;
    }


    /**
     * Esta classe representa um uso de uma carta, que exige um alvo, por exemplo um ataque ou uso de uma magia. A classe armazena a carta usada e a alvo
     */

    private static class UsoCarta {
        private Carta  cartaUsada, cartaAlvo;

        UsoCarta(Carta cartaUsada, Carta cartaAlvo) {
            this.cartaUsada = cartaUsada;
            this.cartaAlvo = cartaAlvo;
        }

        Carta getCartaUsada() {
            return cartaUsada;
        }

        Carta getCartaAlvo() {
            return cartaAlvo;
        }
    }

    /**
     * Cria todas combinações entre as listas, de cartaArrayList
     *
     * @param cartaArrayList lista com as combinações individuais de cada carta
     * @param numeroColunasRemover numero de sublistas que se tem de remover
     * @param indexInicioRemover o primeiro index que se deve utilizar na combinacao
     * Demais paramentros são utilizados para a funcao combinatoriaUsoCartas
     */

    private static void combinatoriaColunasArrayList (ArrayList <ArrayList<UsoCarta>> cartaArrayList,
                                                      int numeroColunasRemover,
                                                      int indexInicioRemover,
                                                      ArrayList<UsoCarta> combinacaoUsoAnterior,
                                                      ArrayList<ArrayList<UsoCarta>> combinacaoUsos,
                                                      int indexAtual) {

        if (numeroColunasRemover != 0) {
            for (int i = indexInicioRemover; i < cartaArrayList.size(); i++) {
                ArrayList <ArrayList<UsoCarta>> cartaArrayListCopia = new ArrayList<>(cartaArrayList);
                cartaArrayList.remove(i);
                combinatoriaColunasArrayList(cartaArrayList,
                        numeroColunasRemover - 1,
                        i,
                        combinacaoUsoAnterior,
                        combinacaoUsos,
                        indexAtual);
                cartaArrayList = new ArrayList<>(cartaArrayListCopia);

            }
        } else {
            indexAtual = 0;
            combinacaoUsoAnterior = new ArrayList<>();
            combinatoriaUsoCartas(cartaArrayList, combinacaoUsoAnterior, combinacaoUsos, indexAtual);
        }
    }

    private static void combinatoriaColunasArrayList (ArrayList <Carta> cartaArrayList,
                                                      int numeroColunasRemover,
                                                      int indexInicioRemover,
                                                      ArrayList <ArrayList<Carta>> combinacaoCartas) {

        if (numeroColunasRemover != 0) {
            for (int i = indexInicioRemover; i < cartaArrayList.size(); i++) {
                ArrayList <Carta> cartaArrayListCopia = new ArrayList<>(cartaArrayList);
                cartaArrayList.remove(i);
                combinatoriaColunasArrayList(cartaArrayList,
                        numeroColunasRemover - 1,
                        i,
                        combinacaoCartas);
                cartaArrayList = new ArrayList<>(cartaArrayListCopia);
            }
        } else {
            combinacaoCartas.add(new ArrayList<>(cartaArrayList));
        }
    }

    /**
     * Combina as sublistas, para retornar todas as combinacoes de usos de cartas possiveis
     *
     * @param listaUsoDeCartas lista base para as combinatórias
     * @param combinacaoUsoAnterior lista incompleta da combinatória
     * @param combinacaoUsos lista que armazena todas as combinacoes para a lista inicial
     * Demais paramentros são utilizados para a funcao combinatoriaUsoCartas
     */

    private static void combinatoriaUsoCartas (ArrayList <ArrayList <UsoCarta>> listaUsoDeCartas,
                                               ArrayList<UsoCarta> combinacaoUsoAnterior,
                                               ArrayList<ArrayList<UsoCarta>> combinacaoUsos,
                                               int indexAtual) {

        ArrayList <UsoCarta> combinacaoAtaqueAtual = new ArrayList<>(combinacaoUsoAnterior);

        if (indexAtual < listaUsoDeCartas.size()) {
            for (int i = 0; i<listaUsoDeCartas.get(indexAtual).size(); i++) {
                if (!combinacaoAtaqueAtual.contains(listaUsoDeCartas.get(indexAtual).get(i))) {
                    combinacaoAtaqueAtual.add(listaUsoDeCartas.get(indexAtual).get(i));
                    combinatoriaUsoCartas(listaUsoDeCartas, combinacaoAtaqueAtual, combinacaoUsos, indexAtual + 1);
                    combinacaoAtaqueAtual.remove(combinacaoAtaqueAtual.size() - 1);
                }
            }
        }
        else {
            combinacaoUsos.add(new ArrayList<>(combinacaoAtaqueAtual));
        }

    }

    /**
     * Processa a jogada, calculando a vida final dos lacaios e oponente
     *
     * @param jogadaAtual jogada a ser processada
     * @param lacaiosOponente lacaios do oponente
     */

    private static void processarJogadaDeCarta (UsoCarta jogadaAtual, ArrayList <CartaLacaio> lacaiosOponente) {

        if (jogadaAtual.getCartaUsada() instanceof CartaLacaio) {
            if (jogadaAtual.getCartaAlvo() == null) {
                vidaOponente -= ((CartaLacaio) jogadaAtual.getCartaUsada()).getAtaque();
            }
            else {
                int vidaMeuLacaio = ((CartaLacaio) jogadaAtual.getCartaUsada()).getVidaAtual() - ((CartaLacaio) jogadaAtual.getCartaAlvo()).getAtaque();
                int vidaOponenteLacaio = ((CartaLacaio) jogadaAtual.getCartaAlvo()).getVidaAtual() - ((CartaLacaio) jogadaAtual.getCartaUsada()).getAtaque();
                ((CartaLacaio) jogadaAtual.getCartaUsada()).setVidaAtual(vidaMeuLacaio);
                ((CartaLacaio) jogadaAtual.getCartaAlvo()).setVidaAtual(vidaOponenteLacaio);
            }
        }
        if (jogadaAtual.getCartaUsada() instanceof CartaMagia) {
            if (((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaTipo() == TipoMagia.BUFF){
                int vidaMeuLacaio = ((CartaLacaio) jogadaAtual.getCartaAlvo()).getVidaAtual() + ((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaDano();
                int ataqueMeuLacaio = ((CartaLacaio) jogadaAtual.getCartaAlvo()).getAtaque() + ((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaDano();
                ((CartaLacaio) jogadaAtual.getCartaAlvo()).setVidaAtual(vidaMeuLacaio);
                ((CartaLacaio) jogadaAtual.getCartaAlvo()).setAtaque(ataqueMeuLacaio);
            }
            if (((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaTipo() == TipoMagia.AREA){
                int danoMagia = ((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaDano();
                for (CartaLacaio lacaioOponente : lacaiosOponente) {
                    lacaioOponente.setVidaAtual(lacaioOponente.getVidaAtual() - danoMagia);
                }
                vidaOponente -= danoMagia;
            }
            if (((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaTipo() == TipoMagia.ALVO) {
                int danoMagia = ((CartaMagia) jogadaAtual.getCartaUsada()).getMagiaDano();
                if (jogadaAtual.getCartaAlvo() == null) {
                    vidaOponente -= danoMagia;
                }
                else {
                    ((CartaLacaio) jogadaAtual.getCartaAlvo()).setVidaAtual(((CartaLacaio) jogadaAtual.getCartaAlvo()).getVidaAtual() - danoMagia);
                }
            }
        }
    }

    /**
     * Reseta a vida dos lacaios e vida do oponente, para o estado inicial to turno
     *
     * @param lacaios meus lacaios
     * @param lacaiosOponente lacaios do oponente
     * @param lacaiosCopia copia do estado inicial dos meus lacaios
     * @param lacaiosOponenteCopia copia do estado inicial dos meus lacaios
     */

    private static void resetaLacaios(ArrayList <CartaLacaio> lacaios,
                                      ArrayList <CartaLacaio> lacaiosOponente,
                                      ArrayList <CartaLacaio> lacaiosCopia,
                                      ArrayList <CartaLacaio> lacaiosOponenteCopia) {

        for (int k = 0; k < lacaios.size(); k++) {
            lacaios.get(k).setVidaAtual(lacaiosCopia.get(k).getVidaAtual());
            lacaios.get(k).setVidaMaxima(lacaiosCopia.get(k).getVidaMaxima());
            lacaios.get(k).setAtaque(lacaiosCopia.get(k).getAtaque());
        }
        for (int k = 0; k < lacaiosOponente.size(); k++) {
            lacaiosOponente.get(k).setVidaAtual(lacaiosOponenteCopia.get(k).getVidaAtual());
            lacaiosOponente.get(k).setVidaMaxima(lacaiosOponenteCopia.get(k).getVidaMaxima());
            lacaiosOponente.get(k).setAtaque(lacaiosOponenteCopia.get(k).getAtaque());
        }

        vidaOponente = vidaOponenteCopia;

    }

    /**
     * Verifica se a jogada é valida para o momento atual do jogo de acordo com o modo de verificação
     *
     * @param jogadaVerificar jogada que se quer verificar
     * @param MODO_VERIFICAR modo que se quer verificar a jogada CURVA MANA, CONTROLE e GENERICO
     * @param lacaiosOponente lacaios do oponente
     * @return boolean se a jogada é valida ou não para o modo de jogo
     */

    private static boolean verificaJogadaValida (ArrayList <UsoCarta> jogadaVerificar,
                                                 int MODO_VERIFICAR,
                                                 ArrayList <CartaLacaio> lacaiosOponente) {

        boolean jogadaValida = true;
        switch (MODO_VERIFICAR) {
            case MODO_CONTROLE:
                for (UsoCarta aJogadaVerificar1 : jogadaVerificar) {
                    Carta cartaUsada = aJogadaVerificar1.getCartaUsada();
                    Carta cartaAlvo = aJogadaVerificar1.getCartaAlvo();
                    if (cartaUsada instanceof CartaMagia) {
                        if (((CartaMagia) cartaUsada).getMagiaTipo() == TipoMagia.ALVO) {
                            if (cartaAlvo != null) {
                                int danoCartaUsada = ((CartaMagia) cartaUsada).getMagiaDano();
                                if (cartaAlvo instanceof CartaLacaio) {
                                    int vidaCartaAlvo = ((CartaLacaio) cartaAlvo).getVidaAtual();
                                    int diferencaDanoVida = vidaCartaAlvo - danoCartaUsada;
                                    if (diferencaDanoVida < -1 || diferencaDanoVida > 0) {
                                        jogadaValida = false;
                                        break;
                                    }
                                }
                            }
                        } else if (((CartaMagia) cartaUsada).getMagiaTipo() == TipoMagia.AREA) {
                            if (lacaiosOponente.size() < 2) {
                                jogadaValida = false;
                                break;
                            }
                        }
                    } else {
                        if (cartaAlvo != null) {
                            if (((CartaLacaio) cartaUsada).getVidaAtual() - ((CartaLacaio) cartaAlvo).getAtaque() <= 0) {
                                jogadaValida = false;
                                break;
                            }
                            if (((CartaLacaio) cartaAlvo).getVidaAtual() - ((CartaLacaio) cartaUsada).getAtaque() > 0) {
                                jogadaValida = false;
                                break;
                            }
                        }
                    }
                }
                break;
            case MODO_CURVA_MANA:
                for (UsoCarta jogadaVerificarAtual : jogadaVerificar) {
                    Carta cartaUsada = jogadaVerificarAtual.getCartaUsada();
                    Carta cartaAlvo = jogadaVerificarAtual.getCartaAlvo();
                    if (cartaUsada instanceof CartaMagia) {
                        if (((CartaMagia) cartaUsada).getMagiaTipo() == TipoMagia.ALVO) {
                            if (cartaAlvo != null) {
                                if (cartaAlvo instanceof CartaLacaio) {
                                    int custoManaCartaUsada = (cartaUsada).getMana();
                                    int custoManaCartaAlvo = cartaAlvo.getMana();
                                    int danoCartaUsada = ((CartaMagia) cartaUsada).getMagiaDano();
                                    int vidaCartaAlvo = ((CartaLacaio) cartaAlvo).getVidaAtual();
                                    if (vidaCartaAlvo - danoCartaUsada > 0 || custoManaCartaAlvo - custoManaCartaUsada < 0) {
                                        jogadaValida = false;
                                        break;
                                    }
                                }
                            }
                        }
                        if (((CartaMagia) cartaUsada).getMagiaTipo() == TipoMagia.AREA) {
                            if (cartaAlvo != null) {
                                int custoManaCartaUsada = (cartaUsada).getMana();
                                int danoCartaUsada = ((CartaMagia) cartaUsada).getMagiaDano();
                                int custoManaLacaiosMortos = 0;
                                for (CartaLacaio lacaioOponente : lacaiosOponente) {
                                    if (lacaioOponente.getVidaAtual() - danoCartaUsada <= 0) {
                                        custoManaLacaiosMortos += lacaioOponente.getMana();
                                    }
                                }
                                if (custoManaCartaUsada <= custoManaLacaiosMortos) {
                                    jogadaValida = false;
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            case MODO_GENERICO:
                for (UsoCarta aJogadaVerificar : jogadaVerificar) {
                    Carta cartaUsada = aJogadaVerificar.getCartaUsada();
                    CartaLacaio cartaAlvo;
                    if (aJogadaVerificar.getCartaAlvo() != null) {
                        cartaAlvo = (CartaLacaio) aJogadaVerificar.getCartaAlvo();
                        if (cartaAlvo.getVidaAtual() <= 0 ) {
                            jogadaValida = false;
                            break;
                        }
                    }
                    if (cartaUsada instanceof CartaLacaio) {
                        if (((CartaLacaio) cartaUsada).getVidaAtual() <= 0) {
                            jogadaValida = false;
                            break;
                        }
                    }
                    processarJogadaDeCarta(aJogadaVerificar, lacaiosOponente);
                }
                break;
        }

        return jogadaValida;
    }

    /**
     * Processa a jogada, calculando a vida final dos lacaios e oponente
     *
     * @param jogadaProcessar jogada a ser processada
     * @param lacaiosOponente lacaios do oponente
     */

    private static void processarJogada (ArrayList <UsoCarta> jogadaProcessar,
                                         ArrayList <CartaLacaio> lacaiosOponente) {

        for (UsoCarta aJogadaProcessar : jogadaProcessar) {
            processarJogadaDeCarta(aJogadaProcessar, lacaiosOponente);
        }

    }

    /**
     * Calcula o dano de uma lista de lacaios
     *
     * @param lacaios lacaios que se quer calcular o dano
     * @return dano total da lista passada
     */

    private static int calculcarDanoLacaios (ArrayList <CartaLacaio> lacaios) {

        int dano = 0;

        for (CartaLacaio lacaio : lacaios) {
            if (lacaio.getVidaAtual() > 0) {
                dano += lacaio.getAtaque();
            }
        }

        return dano;
    }

    /**
     * Calcula o custo de mana de uma lista de usoCarta
     *
     * @param usoCartas lista que se quer calcular o custo
     * @return custo de mana da lista
     */

    private static int calcularCustoManaUsoCarta (ArrayList <UsoCarta> usoCartas) {

        int custoMana = 0;

        for (UsoCarta usoCarta : usoCartas) {
            Carta cartaUsada = usoCarta.getCartaUsada();
            if (cartaUsada instanceof CartaMagia) {
                custoMana += cartaUsada.getMana();
            }
        }

        return custoMana;
    }

    /**
     * Calcula o custo de mana de uma lista de cartas
     *
     * @param cartas lista que se quer calcular o custo
     * @return custo de mana da lista
     */

    private static int calcularCustoManaCarta (ArrayList <Carta> cartas) {

        int custoMana = 0;

        for (Carta carta : cartas) {
            custoMana += carta.getMana();
        }

        return custoMana;
    }

    /**
     * Encontra a melhor combinacao de lacaios, para um determinado modo de jogo
     *
     * @param combinacoesLacaios lista de jogadas possiveis de lacaios
     * @param MODO_VERIFICAR modo que se quer encontrar a melhor combinacao
     * @return index da melhor combincao para o modo
     */

    private static int melhorCombincaoLacaios (ArrayList<ArrayList<Carta>> combinacoesLacaios, int MODO_VERIFICAR) {

        int maiorCustoManaLacaios = 0;
        int maiorDanoLacaios = 0;
        int indexMelhorCombinacaoLacaios = -1;

        switch (MODO_VERIFICAR){
            case MODO_CONTROLE:
                for (int j = 0; j<combinacoesLacaios.size(); j++) {
                    int custoManaLacaiosJogadaAtual = 0;
                    int danoLacaiosJogadaAtual = 0;
                    for (int k = 0; k<combinacoesLacaios.get(j).size(); k++) {
                        custoManaLacaiosJogadaAtual  += combinacoesLacaios.get(j).get(k).getMana();
                        danoLacaiosJogadaAtual += ((CartaLacaio) combinacoesLacaios.get(j).get(k)).getAtaque();
                    }
                    if (custoManaLacaiosJogadaAtual >= maiorCustoManaLacaios) {
                        if (custoManaLacaiosJogadaAtual == maiorCustoManaLacaios) {
                            if (danoLacaiosJogadaAtual > maiorDanoLacaios) {
                                maiorDanoLacaios = danoLacaiosJogadaAtual;
                                indexMelhorCombinacaoLacaios = j;
                            }
                        }
                        else {
                            maiorCustoManaLacaios = custoManaLacaiosJogadaAtual;
                            indexMelhorCombinacaoLacaios = j;
                        }
                    }
                }
                break;
            case MODO_CURVA_MANA:
                for (int j = 0; j<combinacoesLacaios.size(); j++) {
                    int custoManaLacaiosJogadaAtual = 0;
                    for (int k = 0; k < combinacoesLacaios.get(j).size(); k++) {
                        custoManaLacaiosJogadaAtual += combinacoesLacaios.get(j).get(k).getMana();
                    }
                    if (custoManaLacaiosJogadaAtual >= maiorCustoManaLacaios) {
                        maiorCustoManaLacaios = custoManaLacaiosJogadaAtual;
                        indexMelhorCombinacaoLacaios = j;
                    }
                }
                break;
            default:
                break;
        }



        return indexMelhorCombinacaoLacaios;
    }

    /**
     * Verifica, de acordo com o estado atual do jogo, se a jogda possui um custo de mana abaixo ou igual do valor a minhaMana, se  custo for maior, a jogada é retirada da lista
     *
     * @param combinacoesUsoCartas lista que se quer verificar os custo
     */

    private static void verificarCustoManaUsoCartaValido (ArrayList<ArrayList<UsoCarta>> combinacoesUsoCartas) {
        for (int i = 0; i<combinacoesUsoCartas.size(); i++) {
            int custoManaCombo = 0;
            for (int j = 0; j<combinacoesUsoCartas.get(i).size(); j++) {
                custoManaCombo += combinacoesUsoCartas.get(i).get(j).getCartaUsada().getMana();
            }
            if (custoManaCombo > minhaMana) {
                combinacoesUsoCartas.remove(i);
                i--;
            }
        }
    }

    /**
     * Verifica, de acordo com o estado atual do jogo, se a jogda possui um custo de mana abaixo ou igual do valor a minhaMana, se o custo for maior, a jogada é retirada da lista
     *
     * @param combinacoesCartas lista que se quer verificar os custo
     */

    private static void verificarCustoManaCartaValido (ArrayList<ArrayList<Carta>> combinacoesCartas) {

        for (int i = 0; i<combinacoesCartas.size(); i++) {
            int custoManaCombo = 0;
            for (int j = 0; j<combinacoesCartas.get(i).size(); j++) {
                custoManaCombo += combinacoesCartas.get(i).get(j).getMana();
            }
            if (custoManaCombo > minhaMana) {
                combinacoesCartas.remove(i);
                i--;
            }
        }
    }

    /**
     * Verifica, de acordo com o estado atual do jogo, se a jogada de lacaios não ira superar 7 lacaios na mesa, se o numero for maior, a combinação é removida da lista
     *
     * @param combinacoesLacaios lista que se quer verificar os custo
     * @param lacaios lacaios no meu campo
     */

    private static void verificaNumeroLacaios (ArrayList <ArrayList<Carta>> combinacoesLacaios, ArrayList <CartaLacaio> lacaios) {


        for (int i = 0; i<combinacoesLacaios.size(); i++) {
            int numeroTotalLacaiosMesa = lacaios.size() + combinacoesLacaios.get(i).size();
            if (numeroTotalLacaiosMesa > 7) {
                combinacoesLacaios.remove(i);
                i--;
            }
        }
    }

    /**
     * Realiza as jgoadas do uso de cartas
     *
     * @param combinacoesJogadas lista de jogadas
     * @param melhorIndex o index que se deseja realizar a jogda
     * @param mao mao atual
     * @param minhasJogadas minhas jogadas
     */

    private static void jogadaMagiaEAtaque (ArrayList <ArrayList<UsoCarta>> combinacoesJogadas,
                                                          int melhorIndex,
                                                          ArrayList <Carta> mao,
                                                          ArrayList <Jogada> minhasJogadas) {

        for (int i = 0; i<combinacoesJogadas.get(melhorIndex).size(); i++) {
            if (combinacoesJogadas.get(melhorIndex).get(i).getCartaUsada() instanceof CartaLacaio) {
                Jogada jogada = new Jogada(TipoJogada.ATAQUE,
                        combinacoesJogadas.get(melhorIndex).get(i).getCartaUsada(),
                        combinacoesJogadas.get(melhorIndex).get(i).getCartaAlvo());
                minhasJogadas.add(jogada);
            }
            if (combinacoesJogadas.get(melhorIndex).get(i).getCartaUsada() instanceof CartaMagia) {
                Jogada jogada = new Jogada(TipoJogada.MAGIA,
                        combinacoesJogadas.get(melhorIndex).get(i).getCartaUsada(),
                        combinacoesJogadas.get(melhorIndex).get(i).getCartaAlvo());
                mao.remove(combinacoesJogadas.get(melhorIndex).get(i).getCartaUsada());
                minhasJogadas.add(jogada);
            }
        }
    }

    /**
     * Realiza as jgoadas do uso de ataque
     *
     * @param combinacoesJogadas lista de jogadas
     * @param melhorIndex o index que se deseja realizar a jogda
     * @param mao mao atual
     * @param minhasJogadas minhas jogadas
     */

    private static void jogadaLacaio (ArrayList<ArrayList<Carta>> combinacoesJogadas,
                                                    int melhorIndex,
                                                    ArrayList <Carta> mao,
                                                    ArrayList <Jogada> minhasJogadas) {

        for (int i = 0; i<combinacoesJogadas.get(melhorIndex).size(); i++) {
            Jogada jogada = new Jogada(TipoJogada.LACAIO,
                    combinacoesJogadas.get(melhorIndex).get(i),
                    null);
            mao.remove(combinacoesJogadas.get(melhorIndex).get(i));
            minhasJogadas.add(jogada);
        }

    }

    private static void poderHeroico (ArrayList <Jogada> minhasJogadas) {

        if (minhaMana > 2) {
            Jogada jogada = new Jogada(TipoJogada.PODER, null, null);
            minhasJogadas.add(jogada);
        }
    }
}
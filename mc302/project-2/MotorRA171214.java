import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashSet;

/**
 * Esta classe representa o motor, que processa as jogadas e as executa, para o jogo LaMa (Lacaios & Magias).
 * @see java.lang.Object
 * @author Felipe Pessina
 */

public class MotorRA171214 extends Motor {

    /**
     * O método construtor do Motor.
     *
     * @param deck1 Armazena o deck do jogaador 1
     * @param deck2 Armazena o deck do jogador 2
     * @param mao1 Armazena a mao do jogador 1
     * @param mao2 Armazena a mao do jogador 2
     * @param jogador1 Instancia do jogador 1
     * @param jogador2 Instancia do jogador 2
     * @param verbose Indica se as as mensagens de log, dem ser exibidas
     * @param tempoLimitado Indica se deve haver ou não limite de tempo para cada jogada
     * @param saidaArquivo Indica se os logs devem ser printados em um arquivo
     * @param funcionalidadesAtivas Indica quais funcionalidades devem estar ativas, Provocas, Investida, Ataque Duplo
     */
    public MotorRA171214(Baralho deck1, Baralho deck2, ArrayList<Carta> mao1,
                         ArrayList<Carta> mao2, Jogador jogador1, Jogador jogador2,
                         int verbose, int tempoLimitado, PrintWriter saidaArquivo, EnumSet<Funcionalidade> funcionalidadesAtivas) {
        super(deck1, deck2, mao1, mao2, jogador1, jogador2, verbose,
                tempoLimitado, saidaArquivo, funcionalidadesAtivas);
        imprimir("========================");
        imprimir("*** Classe "+this.getClass().getName()+" inicializada.");
        imprimir("Funcionalidade ativas no Motor:");
        imprimir("INVESTIDA: "+(this.funcionalidadesAtivas.contains(Funcionalidade.INVESTIDA)?"SIM":"NAO"));
        imprimir("ATAQUE_DUPLO: "+(this.funcionalidadesAtivas.contains(Funcionalidade.ATAQUE_DUPLO)?"SIM":"NAO"));
        imprimir("PROVOCAR: "+(this.funcionalidadesAtivas.contains(Funcionalidade.PROVOCAR)?"SIM":"NAO"));
        imprimir("========================");
    }

    private int jogador; // 1 == turno do jogador1, 2 == turno do jogador2.
    private int turno;
    private int nCartasHeroi1;
    private int nCartasHeroi2;

    private Mesa mesa;

    // "Apontadores" - Assim podemos programar genericamente os métodos para funcionar com ambos os jogadores
    private ArrayList<Carta> mao;
    private ArrayList<Carta> lacaios;
    private ArrayList<Carta> lacaiosOponente;

    // "Memória" - Para marcar ações que só podem ser realizadas uma vez por turno.
    private boolean poderHeroicoUsado;
    private ArrayList<Integer> lacaiosAtacaramID;

    /**
     * O método executarPartida, executa as jogadas, realizando as chamadas para os jogadores decidirem os movimentos, e processar os movimentos
     */

    @Override
    public int executarPartida() throws LamaException {
        vidaHeroi1 = vidaHeroi2 = 30;
        manaJogador1 = manaJogador2 = 1;
        nCartasHeroi1 = cartasIniJogador1;
        nCartasHeroi2 = cartasIniJogador2;
        ArrayList<Jogada> movimentos = new ArrayList<Jogada>();
        int noCardDmgCounter1 = 1;
        int noCardDmgCounter2 = 1;
        turno = 1;

        for(int k = 0; k < 60; k++){
            imprimir("\n=== TURNO "+turno+" ===\n");
            // Atualiza mesa (com cópia profunda)
            @SuppressWarnings("unchecked")
            ArrayList<CartaLacaio> lacaios1clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa1);
            @SuppressWarnings("unchecked")
            ArrayList<CartaLacaio> lacaios2clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa2);
            mesa = new Mesa(lacaios1clone, lacaios2clone, vidaHeroi1, vidaHeroi2, nCartasHeroi1+1, nCartasHeroi2, turno>10?10:turno, turno>10?10:(turno==1?2:turno));
            this.manaJogador1 = mesa.getManaJog1();
            this.manaJogador2 = mesa.getManaJog2();

            // Apontadores para jogador1
            mao = maoJogador1;
            lacaios = lacaiosMesa1;
            lacaiosOponente = lacaiosMesa2;
            jogador = 1;


            // Processa o turno 1 do Jogador1
            imprimir("\n----------------------- Começo de turno para Jogador 1:");
            long startTime, endTime, totalTime;

            // Cópia profunda de jogadas realizadas.
            @SuppressWarnings("unchecked")
            ArrayList<Jogada> cloneMovimentos1 = (ArrayList<Jogada>) UnoptimizedDeepCopy.copy(movimentos);

            startTime = System.nanoTime();
            if( baralho1.getCartas().size() > 0) {
                if(nCartasHeroi1 >= maxCartasMao) {
                    movimentos = jogador1.processarTurno(mesa, null, cloneMovimentos1);
                    comprarCarta(); // carta descartada
                }
                else {
                    Carta nova = comprarCarta();
                    mao.add(nova);
                    nCartasHeroi1++;
                    movimentos = jogador1.processarTurno(mesa, (Carta) UnoptimizedDeepCopy.copy(nova), cloneMovimentos1);
                }

            }
            else{
                imprimir("Fadiga: O Herói 1 recebeu " + noCardDmgCounter1 + " de dano por falta de cartas no baralho. (Vida restante: "+(vidaHeroi1-noCardDmgCounter1)+").");
                vidaHeroi1 -= noCardDmgCounter1++;
                if( vidaHeroi1 <= 0){
                    // Jogador 2 venceu
                    imprimir("O jogador 2 venceu porque o jogador 1 recebeu um dano mortal por falta de cartas ! (Dano : " +(noCardDmgCounter1-1)+ ", Vida Herói 1: "+vidaHeroi1+")");
                    return 2;
                }
                movimentos = jogador1.processarTurno(mesa, null, cloneMovimentos1);
            }
            endTime = System.nanoTime();
            totalTime = endTime - startTime;
            if( tempoLimitado!=0 && totalTime > 3e8){ // 300ms
                // Jogador 2 venceu, Jogador 1 excedeu limite de tempo
                return 2;
            }
            else
                imprimir("Tempo usado em processarTurno(): "+totalTime/1e6+"ms");

            // Começa a processar jogadas do Jogador 1
            this.poderHeroicoUsado = false;
            this.lacaiosAtacaramID = new ArrayList<>();
            for(int i = 0; i < movimentos.size(); i++){
                processarJogada (movimentos.get(i));
            }

            if( vidaHeroi2 <= 0){
                // Jogador 1 venceu
                return 1;
            }

            // Atualiza mesa (com cópia profunda)
            @SuppressWarnings("unchecked")
            ArrayList<CartaLacaio> lacaios1clone2 = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa1);
            @SuppressWarnings("unchecked")
            ArrayList<CartaLacaio> lacaios2clone2 = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa2);

            mesa = new Mesa(lacaios1clone2, lacaios2clone2, vidaHeroi1, vidaHeroi2, nCartasHeroi1, nCartasHeroi2+1, turno>10?10:turno, turno>10?10:(turno==1?2:turno));

            // Apontadores para jogador2
            mao = maoJogador2;
            lacaios = lacaiosMesa2;
            lacaiosOponente = lacaiosMesa1;
            jogador = 2;

            // Processa o turno 1 do Jogador2
            imprimir("\n\n----------------------- Começo de turno para Jogador 2:");

            // Cópia profunda de jogadas realizadas.
            @SuppressWarnings("unchecked")
            ArrayList<Jogada> cloneMovimentos2 = (ArrayList<Jogada>) UnoptimizedDeepCopy.copy(movimentos);

            startTime = System.nanoTime();


            if( baralho2.getCartas().size() > 0){
                if(nCartasHeroi2 >= maxCartasMao){
                    movimentos = jogador2.processarTurno(mesa, null, cloneMovimentos2);
                    comprarCarta(); // carta descartada
                }
                else {
                    Carta nova = comprarCarta();
                    mao.add(nova);
                    nCartasHeroi2++;
                    movimentos = jogador2.processarTurno(mesa, (Carta) UnoptimizedDeepCopy.copy(nova), cloneMovimentos2);
                }
            }
            else{
                imprimir("Fadiga: O Herói 2 recebeu "+noCardDmgCounter2+" de dano por falta de cartas no baralho. (Vida restante: "+(vidaHeroi2-noCardDmgCounter2)+").");
                vidaHeroi2 -= noCardDmgCounter2++;
                if( vidaHeroi2 <= 0){
                    // Vitoria do jogador 1
                    imprimir("O jogador 1 venceu porque o jogador 2 recebeu um dano mortal por falta de cartas ! (Dano : " +(noCardDmgCounter2-1)+ ", Vida Herói 2: "+vidaHeroi2 +")");
                    return 1;
                }
                movimentos = jogador2.processarTurno(mesa, null, cloneMovimentos2);
            }

            endTime = System.nanoTime();
            totalTime = endTime - startTime;
            if( tempoLimitado!=0 && totalTime > 3e8){ // 300ms
                // Limite de tempo pelo jogador 2. Vitoria do jogador 1.
                return 1;
            }
            else
                imprimir("Tempo usado em processarTurno(): "+totalTime/1e6+"ms");

            this.poderHeroicoUsado = false;
            this.lacaiosAtacaramID = new ArrayList<>();
            for(int i = 0; i < movimentos.size(); i++){
                processarJogada (movimentos.get(i));
            }
            if( vidaHeroi1 <= 0){
                // Vitoria do jogador 2
                return 2;
            }
            turno++;
        }

        // Nunca vai chegar aqui dependendo do número de rodadas
        imprimir("Erro: A partida não pode ser determinada em mais de 60 rounds. Provavel BUG.");
        throw new LamaException(-1, null, "Erro desconhecido. Mais de 60 turnos sem termino do jogo.", 0);
    }

    /**
     * O método processarJogada, realiza chamadas para processar cada movimento do jogador, Ataque, Lacaio, Magia e Poder
     *
     * @param umaJogada Variavel que armazena a jogada a ser processada
     */
    protected void processarJogada(Jogada umaJogada) throws LamaException {
        String erroMensagem;
        switch(umaJogada.getTipo()){
            case ATAQUE:
                // TODO: Um ataque foi realizado... quem atacou? quem foi atacado? qual o dano? o alvo morreu ou ficou com quanto de vida? Trate o caso do herói como alvo também.
                if (umaJogada.getCartaJogada() instanceof CartaLacaio) {
                    ataqueLacaio(jogador, umaJogada);
                    break;
                }
                erroMensagem = "Tentou usar uma jogada LACAIO, mas a cartaJogada nao era lacaio.";
                throw new LamaException(5, umaJogada, erroMensagem, jogador==1?2:1);
            case LACAIO:
                baixarCartaLacaio(jogador, umaJogada);
                break;
            case MAGIA:
                // TODO: Uma magia foi usada... é de área, alvo ou buff? Se de alvo ou buff, qual o lacaio receberá o dano/buff ?
                usarCartaMagia(jogador, umaJogada);
                break;
            case PODER:
                // TODO: O poder heroico foi usado. Qual o alvo ?
                poderHeroico(jogador, umaJogada);
                break;
            default:
                break;
        }
        return;
    }

    /**
     * O método jogarCartaMao, realiza o processamento para utilizar uma carta da Mao tanto Lacaio quanto Magia e chama alteraMana verificando.
     *
     * @param jogada Jogada a ser processada
     * @param jogador Jogador atual
     * @return carta que foi removida da mão, e irá ser utilizada
     */

    private Carta jogarCartaMao (Jogada jogada, int jogador) throws LamaException {
        Carta cartaUsada = contemCarta(mao, jogada.getCartaJogada());

        if (cartaUsada != null) {
            alteraManaJogador(cartaUsada.getMana(), jogador, jogada);
            mao.remove(cartaUsada);
            imprimir("\n" + "A carta. ID = " + jogada.getCartaJogada().getID() + " foi baixada a mesa");
            if (jogador == 1) {
                --this.nCartasHeroi1;
            }
            else {
                --this.nCartasHeroi2;
            }
            return cartaUsada;
        }

        StringBuilder cartasMao = new StringBuilder();
        for (Carta aMao : mao)
            cartasMao.append(aMao.getID()).append(", ");

        String erroMensagem = "Tentou usar carta que nao possui na mao. ID carta=:" + cartaUsada.getID() + ". IDs de cartas na mao= " + cartasMao;
        throw new LamaException(1, jogada, erroMensagem, jogador==1?2:1);
    }

    /**
     * O método alteraManaJogador, verifica se o jogador possui mana disponivel para a jogada, e altera a mana do respectivo jogador.
     *
     * @param mana mana utilizada na jogada
     * @param jogador jogador atual
     * @param jogada jogada atual
     */

    private void alteraManaJogador (int mana, int jogador, Jogada jogada) throws LamaException {

        if (jogador == 1) {
            if (this.manaJogador1 >= mana) {
                this.manaJogador1 -= mana;
                imprimir("\n" + "O jogadaor usou " + mana + " de mana e lhe resta " + this.manaJogador1);
            }
            else {
                String erroMensagem;
                if (jogada.getTipo() == TipoJogada.LACAIO || jogada.getTipo() == TipoJogada.MAGIA) {
                    erroMensagem = "Quantidade de mana excedida na jogada da carta. TipoJogada= " + jogada.getTipo() +
                            ". A mana necessária é  " + jogada.getCartaJogada().getMana() + "  e o jogador possui: " + this.manaJogador1;
                } else {
                    erroMensagem = "Quantidade de mana excedida na jogada da carta. TipoJogada= " + jogada.getTipo() +
                            ". A mana necessária é 2 e o jogador possui: " + this.manaJogador1;
                }
                throw new LamaException(2, jogada, erroMensagem, 2);
            }
        }
        else {
            if (this.manaJogador2 >= mana) {
                this.manaJogador2 -= mana;
                imprimir("\n" + "O jogadaor usou " + mana + " de mana e lhe resta " + this.manaJogador2);
            }
            else {
                String erroMensagem;
                if (jogada.getTipo() == TipoJogada.LACAIO || jogada.getTipo() == TipoJogada.MAGIA) {
                    erroMensagem = "Quantidade de mana excedida na jogada da carta. TipoJogada= " + jogada.getTipo() +
                            ". A mana necessária é " + jogada.getCartaJogada().getMana() + " e o jogador possui: " + this.manaJogador2;
                } else {
                    erroMensagem = "Quantidade de mana excedida na jogada da carta. TipoJogada= " + jogada.getTipo() +
                            ". A mana necessária é 2 e o jogador possui: " + this.manaJogador2;
                }
                throw new LamaException(2, jogada, erroMensagem, 1);
            }
        }
    }

    /**
     * O método alteraVidaJogador, remove a vida do jogador que sofreu dano
     *
     * @param vida a ser removida do jogador
     * @param jogador jogador atual
     */

    private void alteraVidaJogador (int vida, int jogador) {
        if (jogador == 1) {
            this.vidaHeroi1 -= vida;
            imprimir("\n" + "O jogadaor sofreu " + vida + " de dano e lhe resta " + this.vidaHeroi1 + " de vida");
        }
        else {
            this.vidaHeroi2 -= vida;
            imprimir("\n" + "O jogadaor sofreu " + vida + " de dano e lhe resta " + this.vidaHeroi2 + " de vida");
        }
    }

    /**
     * O método poderHeroico, processa a jogada do tipo poderHeroico
     *
     * @param jogador jogador atual
     * @param jogada jogada a ser processada
     */

    private void poderHeroico (int jogador, Jogada jogada) throws LamaException {
        CartaLacaio alvo = null;
        if (jogada.getCartaAlvo() != null) {
            alvo = (CartaLacaio) contemCarta(lacaiosOponente, jogada.getCartaAlvo());
            if (alvo == null) {
                String erroMensagem = "Lacaio inválido de alvo do ataque. ID carta alvo = " + jogada.getCartaAlvo().getID() +
                        "ID carta usada = " + jogada.getCartaJogada().getID();
                throw new LamaException(8, jogada, erroMensagem, jogador==1?2:1);
            }
        }

        if (this.funcionalidadesAtivas.contains(Funcionalidade.PROVOCAR)) {
            ArrayList <Carta> lacaiosProvocar = new ArrayList<>();
            for (int i = 0; i<lacaiosOponente.size(); i++) {
                if (((CartaLacaio)lacaiosOponente.get(i)).getEfeito() == TipoEfeito.PROVOCAR)
                    lacaiosProvocar.add(lacaiosOponente.get(i));
            }
            if (lacaiosProvocar.size() > 0) {
                if (alvo == null || !(lacaiosProvocar.contains(alvo))) {
                    String erroMensagem = "Há um Lacaio com provocar na mesa, e o jogador tentou atacar outro alvo.";
                    throw new LamaException(8, jogada, erroMensagem, jogador == 1 ? 2 : 1);
                }
            }
        }

        if (!this.poderHeroicoUsado) {
            if (alvo == null) {
                if (jogador == 1)
                    alteraVidaJogador(1, 2);
                else
                    alteraVidaJogador(1, 1);
                alteraManaJogador(2, jogador, jogada);
                imprimir("\n" + "O jogador usou o poder heroico diretamente contra o jogador adversário");
                this.poderHeroicoUsado = true;
                return;
            }
            else {
                if (jogada.getCartaAlvo() instanceof CartaLacaio) {
                    if (alvo != null) {
                        alvo.setVidaAtual(alvo.getVidaAtual() - 1);
                        alteraVidaJogador(alvo.getAtaque(), jogador);
                        alteraManaJogador(2, jogador, jogada);
                        imprimir("\n" + "O jogador usou o poder heroico no lacaio ID = " + jogada.getCartaAlvo().getID());
                        if (alvo.getVidaAtual() <= 0)
                            lacaiosOponente.remove(alvo);
                        this.poderHeroicoUsado = true;
                        return;
                    }
                }
                String erroMensagem = "Alvo inválido para o poder heroico. ID = " + jogada.getCartaAlvo().getID();
                throw new LamaException(12, jogada, erroMensagem, jogador==1?2:1);
            }
        }

        String erroMensagem = "Poder heroico ja foi usado neste turno";
        throw new LamaException(11, jogada, erroMensagem, jogador==1?2:1);
    }

    /**
     * O método ataqueLacaio, processa o ataque de um lacaio
     *
     * @param jogador jogador atual
     * @param jogada jogada a ser processada
     */

    private void ataqueLacaio (int jogador, Jogada jogada) throws LamaException {
        CartaLacaio cartaLacaio = (CartaLacaio) contemCarta(lacaios, jogada.getCartaJogada());
        CartaLacaio alvo = null;
        if (jogada.getCartaAlvo() != null) {
            alvo = (CartaLacaio) contemCarta(lacaiosOponente, jogada.getCartaAlvo());
            if (alvo == null) {
                String erroMensagem = "Lacaio inválido de alvo do ataque. ID carta alvo = " + jogada.getCartaAlvo().getID() +
                        "ID carta usada = " + jogada.getCartaJogada().getID();
                throw new LamaException(8, jogada, erroMensagem, jogador==1?2:1);
            }
        }

        if (cartaLacaio == null) {
            String erroMensagem = "Lacaio inválido de origem do ataque. ID carta = " + jogada.getCartaJogada().getID();
            throw new LamaException(5, jogada, erroMensagem, jogador == 1 ? 2 : 1);
        }

        if (cartaLacaio.getTurno() == this.turno) {
            String erroMensagem = "Lacaio nao pode atacar no mesmo turno que entrou na mesa. ID Lacaio=" + cartaLacaio.getID();
            throw new LamaException(6, jogada, erroMensagem, jogador == 1 ? 2 : 1);
        }

        if (this.funcionalidadesAtivas.contains(Funcionalidade.ATAQUE_DUPLO) && cartaLacaio.getEfeito() == TipoEfeito.ATAQUE_DUPLO) {
            int numeroAtaquesLacaio = 0;
            for (int i = 0; i<lacaiosAtacaramID.size(); i++) {
                if (lacaiosAtacaramID.get(i) == cartaLacaio.getID())
                    numeroAtaquesLacaio++;
            }
            if (numeroAtaquesLacaio >= 2) {
                String erroMensagem = "Lacaio com Ataque Duplo não pode atacar mais de duas vezes no mesmo turno. ID Lacaio=" + cartaLacaio.getID();
                throw new LamaException(7, jogada, erroMensagem, jogador == 1 ? 2 : 1);
            }
        } else {
            if (lacaiosAtacaramID.contains(cartaLacaio.getID())) {
                String erroMensagem = "Lacaio nao pode atacar mais de uma vez no mesmo turno. ID Lacaio=" + cartaLacaio.getID();
                throw new LamaException(7, jogada, erroMensagem, jogador == 1 ? 2 : 1);
            }
        }

        if (this.funcionalidadesAtivas.contains(Funcionalidade.PROVOCAR)) {
            ArrayList <Carta> lacaiosProvocar = new ArrayList<>();
            for (int i = 0; i<lacaiosOponente.size(); i++) {
                if (((CartaLacaio)lacaiosOponente.get(i)).getEfeito() == TipoEfeito.PROVOCAR)
                    lacaiosProvocar.add(lacaiosOponente.get(i));
            }
            if (lacaiosProvocar.size() > 0) {
                if (alvo == null || !(lacaiosProvocar.contains(alvo))) {
                    String erroMensagem = "Há um Lacaio com provocar na mesa, e o jogador tentou atacar outro alvo. ID Lacaio=" + cartaLacaio.getID();
                    throw new LamaException(8, jogada, erroMensagem, jogador == 1 ? 2 : 1);
                }
            }
        }

        if (alvo == null) {
            alteraVidaJogador(cartaLacaio.getAtaque(), jogador);
            lacaiosAtacaramID.add(cartaLacaio.getID());
            imprimir("\n" + "Jogador = " + jogador + " utilizou o lacaio = " + jogada.getCartaJogada().getID() + " atacando o oponente diretamente");
        } else {
            if (alvo instanceof CartaLacaio) {
                if (alvo != null) {
                    cartaLacaio.setVidaAtual(cartaLacaio.getVidaAtual() - alvo.getAtaque());
                    alvo.setVidaAtual(alvo.getVidaAtual() - cartaLacaio.getAtaque());
                    if (alvo.getVidaAtual() <= 0)
                        lacaiosOponente.remove(alvo);
                    if (cartaLacaio.getVidaAtual() <= 0)
                        lacaios.remove(cartaLacaio);
                    imprimir("\n" + "Jogador = " + jogador + " utilizou o lacaio ID = " + jogada.getCartaJogada().getID() +
                            " atacando o lacaio ID = " + jogada.getCartaAlvo().getID());
                    lacaiosAtacaramID.add(cartaLacaio.getID());
                    return;
                }
            }
            String erroMensagem = "Lacaio inválido de alvo do ataque. ID carta alvo = " + jogada.getCartaAlvo().getID() +
                    "ID carta usada = " + jogada.getCartaJogada().getID();
            throw new LamaException(8, jogada, erroMensagem, jogador==1?2:1);
        }
    }

    /**
     * O método baixarCartaLacaio, processa a jogada de baixar um lacaio a mesa
     *
     * @param jogador jogador atual
     * @param jogada jogada a ser processada
     */

    private void baixarCartaLacaio (int jogador, Jogada jogada) throws LamaException {
        if (!(jogada.getCartaJogada() instanceof CartaLacaio)) {
            String erroMensagem = "Tentou baixar uma carta que nao e lacaio. ID: " + jogada.getCartaJogada().getID();
            throw new LamaException(3, jogada, erroMensagem, jogador==1?2:1);
        } else {
            if (lacaios.size() >= 7) {
                String erroMensagem = "Tentou baixar um lacaio, ja tendo 7 lacaios na mesa. ID carta = " + jogada.getCartaJogada().getID();
                throw new LamaException(4, jogada, erroMensagem, jogador==1?2:1);
            }
            CartaLacaio cartaLacaio = (CartaLacaio) this.jogarCartaMao(jogada, jogador);
            if (this.funcionalidadesAtivas.contains(Funcionalidade.INVESTIDA) && cartaLacaio.getEfeito() == TipoEfeito.INVESTIDA)
                cartaLacaio.setTurno(this.turno - 1);
            else
                cartaLacaio.setTurno(this.turno);
            this.lacaios.add(cartaLacaio);
        }
    }

    /**
     * O método usarCartaMagia, processa a jogada de usar uma carta de magia, Buff, Alvo, Area
     *
     * @param jogador jogador atual
     * @param jogada jogada a ser processada
     */

    private void usarCartaMagia (int jogador, Jogada jogada) throws LamaException {
        if (!(jogada.getCartaJogada() instanceof CartaMagia)) {
            String erroMensagem = "Tentou usar uma carta como magia, que nao e magia. ID: " + jogada.getCartaJogada().getID();
            throw new LamaException(9, jogada, erroMensagem, jogador==1?2:1);
        } else {
            CartaMagia cartaMagia = (CartaMagia) this.jogarCartaMao(jogada, jogador);
            switch (cartaMagia.getMagiaTipo()) {
                case ALVO:
                    if (jogada.getCartaAlvo() == null) {
                        if (jogador == 1)
                            alteraVidaJogador(cartaMagia.getMagiaDano(), 2);
                        else
                            alteraVidaJogador(cartaMagia.getMagiaDano(), 1);
                        imprimir("\n" + "Jogador = " + jogador + " utilizou a magia de alvo ID = " + jogada.getCartaJogada().getID() + " atacando o oponente diretamente");
                    }
                    else {
                        Carta carta = contemCarta(lacaiosOponente, jogada.getCartaAlvo());
                        if (carta instanceof CartaLacaio) {
                            if (lacaiosOponente.contains(carta)) {
                                CartaLacaio cartaLacaioAlvo = (CartaLacaio) carta;
                                imprimir("\n" + "Jogador = " + jogador + " utilizou a magia de alvo ID = " + jogada.getCartaJogada().getID() +
                                        " atacando o lacaio ID = " + jogada.getCartaAlvo().getID());
                                cartaLacaioAlvo.setVidaAtual(cartaLacaioAlvo.getVidaAtual() - cartaMagia.getMagiaDano());
                                if (cartaLacaioAlvo.getVidaAtual() <= 0)
                                    lacaiosOponente.remove(cartaLacaioAlvo);
                                return;
                            }
                        }
                        String erroMensagem = "Tentou usar uma magia de alvo, em um alvo invalido. ID carta usada: " +
                                jogada.getCartaJogada().getID() + " ID carta alvo: " + jogada.getCartaAlvo().getID();
                        throw new LamaException(10, jogada, erroMensagem, jogador==1?2:1);
                    }
                    break;
                case AREA:
                    imprimir("\n" + "Jogador = " + jogador + " utilizou a magia de area ID = " + jogada.getCartaJogada().getID());
                    for (Carta lacaio : lacaiosOponente)
                        ((CartaLacaio)lacaio).setVidaAtual(((CartaLacaio) lacaio).getVidaAtual() - cartaMagia.getMagiaDano());

                    for (int i = 0; i <lacaiosOponente.size(); i++) {
                        if (((CartaLacaio) lacaiosOponente.get(i)).getVidaAtual() <= 0) {
                            lacaiosOponente.remove(lacaiosOponente.get(i));
                            i--;
                        }
                    }

                    if (jogador == 1)
                        alteraVidaJogador(cartaMagia.getMagiaDano(), 2);
                    else
                        alteraVidaJogador(cartaMagia.getMagiaDano(), 1);
                    break;
                case BUFF:
                    Carta carta = contemCarta(lacaios, jogada.getCartaAlvo());
                    if (!(carta instanceof CartaLacaio)) {
                        String erroMensagem = "Tentou usar uma magia de buff, em um alvo invalido. ID carta usada: " +
                                jogada.getCartaJogada().getID() + " ID carta alvo: " + jogada.getCartaAlvo().getID();
                        throw new LamaException(10, jogada, erroMensagem, jogador==1?2:1);
                    } else {
                        CartaLacaio cartaLacaio = (CartaLacaio) carta;
                        imprimir("\n" + "Jogador = " + jogador + " utilizou a magia de buff ID = " + jogada.getCartaJogada().getID() +
                                " para buffar o lacaio ID = " + jogada.getCartaAlvo().getID());
                        cartaLacaio.setVidaAtual(cartaLacaio.getVidaAtual() + cartaMagia.getMagiaDano());
                        cartaLacaio.setAtaque(cartaLacaio.getAtaque() + cartaMagia.getMagiaDano());
                    }
                    break;
            }
        }
    }

    /**
     * O método comprarCarta, remove um carta do baralho
     * @return carta sacada do baralho
     */

    private Carta comprarCarta(){
        if(this.jogador == 1){
            if(baralho1.getCartas().size() <= 0)
            throw new RuntimeException("Erro: Não há mais cartas no baralho para serem compradas.");
            Carta nova = baralho1.comprarCarta();
            imprimir("\n" + "Jogador = " + jogador + " comprou a carta de ID = " + nova.getID());
            return (Carta) UnoptimizedDeepCopy.copy(nova);
        }
        else{
            if(baralho2.getCartas().size() <= 0)
                throw new RuntimeException("Erro: Não há mais cartas no baralho para serem compradas.");
            Carta nova = baralho2.comprarCarta();
            imprimir("\n" + "Jogador = " + jogador + " comprou a carta de ID = " + nova.getID());
            return (Carta) UnoptimizedDeepCopy.copy(nova);
        }
    }

    /**
     * O método contemCarta, verifica se a carta a ser jogada esta presente na mesa ou mao do jogador, para impedir fraudes
     *
     * @param list lista para verificar se a carta esta contida
     * @param carta carta a ser verificada
     * @return retorna a carta se ela existe, e null se ela não existe na lista
     */

    private Carta contemCarta (ArrayList <Carta> list, Carta carta) {
        int id  = carta.getID();
        for (int i = 0; i<list.size(); i++) {
            if (list.get(i).getID() == id)
                return list.get(i);
        }

        return null;
    }

}

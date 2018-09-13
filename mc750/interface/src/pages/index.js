import React, {Component} from 'react'
import {Grid, Container, Modal, Form, Button, Icon} from 'semantic-ui-react'

export default class PageIndex extends Component {
  state = {
    timer: 0,
    rounds: 0,
    phrase1: '',
    phrase2: null,
    phrase3: null,
    modal: false
  }

  componentWillMount() {
    window.addEventListener('keydown', this.handleKeyboardInput.bind(this));
  }

  timer = 0;
  timerUpdater = null;


  handleKeyboardInput = (event) => {
    const code = event.keyCode
    console.log(code)
    if (code == 87) { // w
      this.setState({rounds: this.state.rounds + 1})
      this.setState({phrase1: 'Pontuação: ' + this.state.rounds})
      this.setState({phrase2: null})
      this.setState({phrase3: null})
      this.setState({modal: false})
    } else if (code == 76) { // l
      this.setState({timer: this.timer})
      clearInterval(this.timerUpdater)
      this.setState({modal: true})
      this.setState({phrase1: 'Pontuação: ' + this.state.rounds})
      this.setState({phrase2: 'Tempo Jogando: ' + this.state.timer + 's'})
      this.setState({phrase3: 'Nosso trabalho tem o objetivo de introduzir o conceito de tempo profundo aos usuários. Este conceito se refere à uma concepção mais abstrata de tempo, na qual dificilmente acabamos refletindo sobre. Por exemplo: o tempo geológico, tempo de vida dos astros e quantidades de tempo imensuráveis para nosso escopo, que é de apenas de algumas dezenas de anos. Entretanto também há o conceito de flowstate envolvido, que se trata de uma diferente percepção do tempo, geralmente envolvida em atividades de moderada/alta concentração, neste estado podemos perceber o tempo passar de maneira diferente. Esperamos que tenha funcionado para você!',})
    } else if (code == 83) { // s
      this.setState({modal: false})
      this.setState({phrase1: 'Jogando ...'})
      this.setState({phrase2: null})
      this.setState({phrase3: null})
      this.setState({timer: 0})
      this.setState({rounds: 0})
      this.timer = 0;
      this.timerUpdater = setInterval(() => {
        this.timer += 1;
      }, 1000);
    }
  }

  render () {
    return (
        <div style={{height:'100vh', display: 'flex', justifyContent: 'center', alignItems: 'center' }}>
          <Modal open={this.state.modal} centered closeIcon={<Icon name='times' size='big' style={{padding: '16px'}} onClick={() => {this.setState({modal: false})}}/>}>
            <Modal.Content>
              <div style={{textAlign:'center', padding:'32px 0px'}}>
                <h2>Quanto segundos você acha que passaram enquanto você estava jogando?</h2>
                <div style={{display:'inline-flex', margin: '0px auto'}}>
                  <Form.Input label='' placeholder='Tempo jogado'/>
                  <Form.Button style={{marginLeft:'16px'}} onClick={() => {this.setState({modal: false})}}>Enviar</Form.Button>
                </div>
              </div>
            </Modal.Content>
          </Modal>
          <Container  style={{border: '1px solid grey', borderRadius:'20px'}}>
              <h1 style={{textAlign: 'center'}}>Flow Machine</h1>
              <ul>
                <li>O objetivo do jogo obter a atenção do jogador, e fazer com que ele perca a noção do tempo</li>
                <li>O jogo consiste em vários turno, cada turno os leds irão acender em uma determinada sequencia e o jogador deve repeti-la apertando os botões correspondentes</li>
                <li>Para iniciar o jogo verifique se o led branco está aceso, se sim basta apertar qualquer botão para iniciá-lo</li>
              </ul>
              <p style={{ textAlign: 'center', marginBottom:'12px'}}>{this.state.phrase1}</p>
              {this.state.phrase2 && <p style={{ textAlign: 'center'}}>{this.state.phrase2}</p>}
              {this.state.phrase3 && <li style={{ textAlign: 'center', padding:'32px'}}>{this.state.phrase3}</li>}
          </Container>
        </div>
    )
  }
}

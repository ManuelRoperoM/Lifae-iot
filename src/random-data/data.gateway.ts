import { Logger } from '@nestjs/common';
import { WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server } from 'socket.io';

@WebSocketGateway(3001, { cors: { origin: '*' } })
export class DataGateway {
  private readonly logger = new Logger(DataGateway.name);

  @WebSocketServer()
  server: Server;

  handleNewData(data: any) {
    this.logger.log('Emitting data:', data.number);
    this.server.emit('data', data);
  }
}

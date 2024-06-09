import { Logger } from '@nestjs/common';
import { WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server } from 'socket.io';

@WebSocketGateway({ cors: { origin: '*' } })
export class DataGateway {
  private readonly logger = new Logger(DataGateway.name);

  @WebSocketServer()
  server: Server;

  handleNewData(data: any) {
    this.server.emit('data', data);
  }
}

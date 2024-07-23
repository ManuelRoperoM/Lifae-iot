import { Injectable, Logger } from '@nestjs/common';
import { DataGateway } from './data.gateway';

@Injectable()
export class RandomDataService {
  private readonly logger = new Logger(RandomDataService.name);
  constructor(private readonly dataGateway: DataGateway) {}
  getSaludo() {
    return 'Hola desde random module!';
  }

  async randomNumber(data: any) {
    const parsedData = JSON.parse(data.number);
    const potenciaP = parsedData['Potencia P'];
    const reactivaQ = parsedData['Reactiva Q'];
    const aparenteS = Math.sqrt(
      Math.pow(potenciaP, 2) + Math.pow(reactivaQ, 2),
    );
    const dataSend = {
      potenciaP: potenciaP,
      reactivaQ: reactivaQ,
      aparenteS: aparenteS,
      factorPotencia: aparenteS != 0 ? potenciaP / aparenteS : 1,
    };
    this.logger.log('dataSend:', dataSend);
    this.dataGateway.handleNewData(dataSend);
    return 'Data recibida';
  }
}

import { Injectable, Logger } from '@nestjs/common';
import { DataGateway } from './data.gateway';
import { Meterings } from './meterings.entity';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
@Injectable()
export class MeteringsService {
  private readonly logger = new Logger(MeteringsService.name);
  constructor(
    private readonly dataGateway: DataGateway,
    @InjectRepository(Meterings)
    private readonly meteringsRepository: Repository<Meterings>,
  ) {}
  getSaludo() {
    return 'Hola desde random module!';
  }

  async calculatePowers(data: any) {
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

  async saveMetering(data: any) {
    return this.meteringsRepository.save(data);
  }

  async findAll(): Promise<Meterings[]> {
    return this.meteringsRepository.find();
  }
}

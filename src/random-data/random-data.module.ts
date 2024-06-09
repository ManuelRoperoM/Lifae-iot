import { Module } from '@nestjs/common';
import { RandomDataController } from './random-data.controller';
import { RandomDataService } from './random-data.service';
import { DataGateway } from './data.gateway';

@Module({
  controllers: [RandomDataController],
  providers: [RandomDataService, DataGateway],
})
export class RandomDataModule {}

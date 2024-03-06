import { Module,Get } from '@nestjs/common';
import { RandomDataController } from './random-data.controller';
import { RandomDataService } from './random-data.service';
import { get } from 'http';

@Module({
  controllers: [RandomDataController],
  providers: [RandomDataService]
})
export class RandomDataModule {}

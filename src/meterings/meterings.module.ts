import { Module } from '@nestjs/common';
import { MeteringsController } from './meterings.controller';
import { MeteringsService } from './meterings.service';
import { DataGateway } from './data.gateway';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Meterings } from './meterings.entity';

@Module({
  controllers: [MeteringsController],
  providers: [MeteringsService, DataGateway],
  imports: [TypeOrmModule.forFeature([Meterings])],
})
export class MeteringsModule {}

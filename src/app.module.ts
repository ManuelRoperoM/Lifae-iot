import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { RandomDataModule } from './random-data/random-data.module';

@Module({
  imports: [RandomDataModule],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
